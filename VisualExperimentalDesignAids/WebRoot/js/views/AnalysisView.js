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
        var analyzer = $(e.currentTarget);
        CurrentResult = Number(analyzer.attr("id").split("_")[1]);
        setLoading(true);
        interface.analysisRequested(analyzer.val());
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
            "data": $.parseJSON(result["data"])
        };
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

}

function refreshOneFactorType() {

}

function refreshTwoFactorType() {

}

function refreshCharts() {

}

function refreshHeatMap() {
}

function addResult() {
    var html = "";
    html += "        <div id=\"result_" + CurrentResultNumber + "\" class=\"section\" style=\"position: relative;\">\n" +
            "            <i class=\"material-icons delete_btn\" style=\"position: absolute; right: 1em; top: .5em; cursor: pointer;\">close</i>\n" +
            "\n" +
            "            <div class=\"row\" style=\"margin: .25em; \">\n" +
            "                <div class=\"col s6 input-field\">\n" +
            "                    <select id=\"analyzer_" + CurrentResultNumber + "\">\n" +
                                     generateAnalyzerOptions() +
            "                    </select>\n" +
            "                    <label>统计分析方法：</label>\n" +
            "                </div>\n" +
            "\n" +
            "                <div class=\"col s6 input-field\" style='display: none;'>\n" +
            "                    <select id=\"type_" + CurrentResultNumber + "\">\n" +
            "                    </select>\n" +
            "                    <label>图表类型：</label>\n" +
            "                </div>\n" +
            "\n" +
            "                <div class=\"col s12\" id=\"charts_" + CurrentResultNumber + "\" style='display: none;'></div>\n" +
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
