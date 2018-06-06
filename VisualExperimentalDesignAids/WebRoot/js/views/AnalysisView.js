var interface = null;

var CurrentResult = -1;
var CurrentResultNumber = 0;
var Analyzers = [];
var Results = [];

$(document).ready(function() {
    $(document).bind("contextmenu", function (e) {
        return false;
    });
    $('#loader').hide();
    $(".modal").modal();
    $('#add_result_btn').attr('disabled', 'disabled').click(function(){
        addResult();
    });
    $('#add_compare_btn').attr('disabled', 'disabled');

    new QWebChannel(qt.webChannelTransport, function (channel) {
        interface = channel.objects.VEDAAnalysisViewInterface;

        interface.analyzerResponse.connect(function(ok, data){
            setLoading(false);
            if (ok) {
                setAnalyzers($.parseJSON(data)["analyzers"]);
            } else {
                information('错误', '读取解析方法错误：' + data);
            }
        });

        interface.analysisResponse.connect(function(ok, data){
            setLoading(false);
            if (ok) {
                refreshResult($.parseJSON(data));
            } else {
                information('错误', '读取解析方法错误：' + data);
            }
        });

        setLoading(true);
        interface.analyzerRequested();
    });

    $('#ResultContainer').on('click', '.delete_btn', function(e){
        var result = $(e.currentTarget).parent();
        var divider = result.next();
        var resultOrder = Number(result.attr("id").split("_")[1]);
        var analyzer = $('#analyzer_' + resultOrder).val();
        for (var i = 0, j = Analyzers.length; i !== j; ++i) {
            if (Analyzers[i]["name"] === analyzer) {
                Analyzers[i]["selected"] = false;
            }
        }

        result.remove();
        divider.remove();
        Results[CurrentResult] = {};
        if ($('#analyzer_' + (CurrentResultNumber - 1)).val() !== null) {
            $('#add_result_btn').removeAttr('disabled');
        }
    }).on('change', 'select', function(e){
        var target = $(e.currentTarget);
        var parts = target.attr("id").split("_");
        CurrentResult = Number(parts[1]);
        if (parts[0] === "analyzer") {
            setLoading(true);
            interface.analysisRequested(target.val());
        } else if (parts[0] === "type") {
            refreshCharts(target.val());
        }
    });
});

function setAnalyzers(analyzers) {
    for (var i = 0, j = analyzers.length; i !== j; ++i) {
        Analyzers.push({
            "name": analyzers[i]["name"],
            "display": analyzers[i]["display"],
            "selected": false
        });
    }
    $('#add_result_btn').removeAttr('disabled');
}

function refreshResult(result) {
    var analyzer = $('#analyzer_' + CurrentResult).val();
    for (var i = 0, j = Analyzers.length; i !== j; ++i) {
        if (Analyzers[i]["name"] === analyzer) {
            Analyzers[i]["selected"] = true;
        }
    }

    if (result["type"] === "Raw") {
        Results[CurrentResult] = {
            "type": "Raw",
            "data": result["data"]
        };
        $('#charts_' + CurrentResult).html("<p>" + result["data"] + "</p>").show();
    } else if (result["type"] === "Table") {
        Results[CurrentResult] = {
            "type": "Table",
            "data": normalizeData($.parseJSON(result["data"]))
        };
        $('#charts_' + CurrentResult).html("").hide();
        refreshType();
    } else if (result["type"] === "Html5") {
        Results[CurrentResult] = {
            "type": "Raw",
            "data": result["data"]
        };
        $('#charts_' + CurrentResult).html(result["data"]).show();
    } else if (result["type"] === "None") {
        Results[CurrentResult] = {
            "type": "None",
            "data": result["data"]
        };
        information("错误", result["data"]);
    }
    $('#add_result_btn').removeAttr('disabled');
}

function refreshType() {
    var factorNumber = 0;
    for (var key in Results[CurrentResult]["data"]) {
        if (key === "xCategories") {
            ++factorNumber;
        }
        if (key === "yCategories") {
            ++factorNumber;
        }
    }
    if (factorNumber === 1) {
        refreshOneFactorType();
    } else if (factorNumber === 2) {
        refreshTwoFactorType();
    }
}

function refreshOneFactorType() {
    var html = "";
    html += "<option selected disabled>请选择图表类型</option>";
    html += "<option value='line'>折线图</option>";
    html += "<option value='area'>面积图</option>";
    var type = $('#type_' + CurrentResult);
    type.parent().show();
    type.html(html).material_select();
}

function refreshTwoFactorType() {
    var html = "";
    html += "<option selected disabled>请选择图表类型</option>";
    html += "<option value='heat'>热力图</option>";
    var type = $('#type_' + CurrentResult);
    type.parent().show();
    type.html(html).material_select();
}

function refreshCharts(key) {
    if (key === "line") {
        refreshLine();
    } else if (key === "area") {
        refreshArea();
    } else if (key === "heat") {
        refreshHeatMap();
    }
}

function refreshLine() {
    $('#charts_' + CurrentResult).highcharts({
        chart: {
            type: 'line'
        },
        title: {
            text: ''
        },
        credits: {
            enabled: false
        },
        yAxis: {
            title: null
        },
        xAxis: {
            xCategories: Results[CurrentResult]["data"]["xCategories"]
        },
        tooltip: {
            split: true
        },
        plotOptions: {
            area: {
                stacking: 'normal',
                lineColor: '#666666',
                lineWidth: 1,
                marker: {
                    lineWidth: 1,
                    lineColor: '#666666'
                }
            }
        },
        series: [{
            data: Results[CurrentResult]["data"]["datas"]
        }]
    }).show();
}

function refreshArea() {
    $('#charts_' + CurrentResult).highcharts({
        chart: {
            type: 'area'
        },
        title: {
            text: null
        },
        credits: {
            enabled: false
        },
        yAxis: {
            title: null
        },
        xAxis: {
            xCategories: Results[CurrentResult]["data"]["xCategories"]
        },
        tooltip: {
            split: true
        },
        plotOptions: {
            area: {
                stacking: 'normal',
                lineColor: '#666666',
                lineWidth: 1,
                marker: {
                    lineWidth: 1,
                    lineColor: '#666666'
                }
            }
        },
        series: [{
            data: Results[CurrentResult]["data"]["datas"]
        }]
    }).show();
}

function refreshHeatMap() {
    $('#charts_' + CurrentResult).highcharts({
        credits: {
            enabled: false
        },
        chart: {
            type: 'heatmap',
            marginTop: 40,
            marginBottom: 80,
            plotBorderWidth: 1
        },
        title: {
            text: ""
        },
        yAxis: {
            categories: Results[CurrentResult]["data"]["yCategories"],
            title: null
        },
        xAxis: {
            categories: Results[CurrentResult]["data"]["xCategories"]
        },
        colorAxis: {
            min: 0,
            minColor: '#FFFFFF',
            maxColor: Highcharts.getOptions().colors[0]
        },
        legend: {
            align: 'right',
            layout: 'vertical',
            margin: 0,
            verticalAlign: 'top',
            y: 25,
            symbolHeight: 280
        },
        tooltip: {
            formatter: function () {
                return '<b>' + this.series.xAxis.categories[this.point.x] + '</b>, <b>' +
                    this.series.yAxis.categories[this.point.y] + '</b>: <b>' + this.point.value + '</b>';
            }
        },
        series: [{
            borderWidth: 1,
            data: Results[CurrentResult]["data"]["datas"],
            dataLabels: {
                enabled: true,
                color: '#000000'
            }
        }]
    }).show();
}

function addResult() {
    var html = "";
    html += "        <div id=\"result_" + CurrentResultNumber + "\" class=\"section\" style=\"position: relative;\">\n" +
            "            <i class=\"material-icons delete_btn\" style=\"position: absolute; right: 1em; top: .5em; cursor: pointer;\">close</i>\n" +
            "\n" +
            "            <div class=\"row\" style=\"margin: .25em; \">\n" +
            "                <div class=\"col s6 input-field\"  style='z-index: 1;'>\n" +
            "                    <select id=\"analyzer_" + CurrentResultNumber + "\">\n" +
                                     generateAnalyzerOptions() +
            "                    </select>\n" +
            "                    <label>统计分析方法：</label>\n" +
            "                </div>\n" +
            "\n" +
            "                <div class=\"col s6 input-field\" style='z-index: 1;'>\n" +
            "                    <select id=\"type_" + CurrentResultNumber + "\">\n" +
            "                    </select>\n" +
            "                    <label>图表类型：</label>\n" +
            "                </div>\n" +
            "\n" +
            "                <div class=\"col s12\" id=\"charts_" + CurrentResultNumber + "\" style='display: none; z-index: 0;'></div>\n" +
            "            </div>\n" +
            "        </div>" +
            "        <div class=\"divider\"></div>";
    $('#ResultContainer').append(html);
    $('select').material_select();
    $('#add_result_btn').attr('disabled', 'disabled');
    Results.push({});
    ++CurrentResultNumber;
}

function generateAnalyzerOptions() {
    var html = "<option value=\"\" disabled selected>请选择统计分析方法：</option>";
    for (var i = 0, j = Analyzers.length; i !== j; ++i) {
        if (!Analyzers[i]["selected"]) {
            html += "<option value=\"" + Analyzers[i]["name"] + "\">" + Analyzers[i]["display"] + "</option>";
        }
    }
    return html;
}

function normalizeData(data) {
    var _datas = [];
    for (var i = 0, j = data["datas"].length; i !== j; ++i) {
        var thisData = [];
        for (var p = 0, q = data["datas"][i].length; p !== q; ++p) {
            thisData[p] = Number(data["datas"][i][p]);
        }
        _datas.push(thisData);
    }
    data["datas"] = _datas;
    return data;
}
