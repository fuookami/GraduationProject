var interface = null;

var ShowMode = true;
var ModifyMode = false;
var CurrentMode = ShowMode;

var CurrentPage = 0;
var CurrentPageNumber = 0;

var read_only_factors = [];
var factors = [];
var batches = [];

$(document).ready(function() {
    $(document).bind("contextmenu",function(e){
        return false;
    });
    $('#loader').hide();
    $('#ModifyView').hide();
    $(".modal").modal();

    $('#ModeSwitch').on('change', function(){
        var showMode = $('#ModeSwitch').prop('checked');
        if (showMode) {
            turnToShowMode();
        } else {
            turnToModifyMode();
        }
    });

    $('#ModifyFormContainer').on('change', 'input', function(e){
        var target = $(e.currentTarget);
        var id = target.attr('id');
        var parts = id.split('_');
        var batch = Number(parts[1]) - 1;
        var factor = Number(parts[3]);
        batches[batch][factor]["content"] = target.val();
    });

    new QWebChannel(qt.webChannelTransport, function (channel) {
        interface = channel.objects.VEDADataViewInterface;

        $('#submit_btn').click(function(){
            setLoading(true);
            interface.dataSubmited(JSON.stringify(getSubmitData()));
        });

        $('#refresh_btn').click(function(){
            setLoading(true);
            interface.dataRequested();
        });

        interface.dataResponse.connect(function(data) {
            refreshData($.parseJSON(data));
            setLoading(false);
        });

        interface.submitResponse.connect(function(ok, info) {
            setLoading(false);
            if (ok) {
                information('结果', '保存成功');
            } else {
                information('结果', '保存失败：' + info);
            }
        });

        setLoading(true);
        interface.dataRequested();
    });
});

function turnToShowMode() {
    CurrentMode = ShowMode;
    $('#Title').html('查看实验方案设计表');
    var html = "<table class=\"bordered striped centered\">\n" +
        "            <thead>\n" +
        "                <tr>\n" +
        "                    <th>实验号</th>\n";

    for (var i = 0, j = factors.length; i !== j; ++i) {
        html += "            <th>" + factors[i] + "</th>\n";
    }

    html += "            </tr>\n" +
        "            </thead>\n" +
        "            <tbody>\n";

    for (var i = 0, j = batches.length; i !== j; ++i) {
        var batch = batches[i];
        html += "        <tr>\n" +
            "                <td>" + (i + 1) + "</td>\n";
        for (var p = 0, q = batch.length; p !== q; ++p) {
            var cell = batch[p];
            html += "        <td>" + generateContent(cell)  + "</td>";
        }
        html += "        </tr>\n";
    }

    html += "        </tbody>\n" +
            "   </table>";

    $('#ShowView').html(html).show();
    $('#ModifyFormContainer').html('');
    $('#ModifyView').hide();

    $('.pushpin-demo-nav').each(function() {
        var $this = $(this);
        var $target = $('#' + $(this).attr('data-target'));
        $this.pushpin({
            top: $target.offset().top,
            bottom: $target.offset().top + $target.outerHeight() - $this.height()
        });
    });
}

function turnToModifyMode() {
    CurrentMode = ModifyMode;
    $('#Title').html('填写实验方案设计表');

    var html = "";
    for (var i = 0, j = CurrentPageNumber; i !== j; ++i) {
        var batch = batches[i];
        var page = i + 1;

        html += "             <div id=\"page_" + page + "\" class=\"container\" style=\"display: none;\">\n" +
            "                        <h5><b>实验号：" + page + "</b></h5>\n";
        for (var p = 0, q = batch.length; p !== q; ++p) {
            var cell = batch[p];
            var factor = factors[p];

            if (read_only_factors.indexOf(factor) !== -1) {
                html += "                <h5 id=\"page_" + page + "_factor_" + p + "\">" + factor + "：" + generateContent(cell) + "</h5>";
            } else {
                html += "                <div class=\"input-field\">\n" +
                    "                        <input id=\"page_" + page + "_factor_" + p + "\" type=\"text\" value=\"" + cell["content"] + "\">\n" +
                    "                        <label id=\"page_" + page + "_factor_" + p + "\">" + generateLabel(cell, factor) + "</label>\n" +
                    "                    </div>"
            }
        }
        html += "</div>";
    }

    $('#ShowView').html('').hide();
    $('#ModifyFormContainer').html(html);
    $('#ModifyView').show();
    Materialize.updateTextFields();

    turnToPage(1);

    $('.pushpin-demo-nav').each(function() {
        var $this = $(this);
        var $target = $('#' + $(this).attr('data-target'));
        $this.pushpin({
            top: $target.offset().top,
            bottom: $target.offset().top + $target.outerHeight() - $this.height()
        });
    });
}

function refreshData(data) {
    read_only_factors = data["read_only_factors"];
    factors = data["factors"];
    batches = data["batches"];

    if (CurrentMode === ShowMode) {
        turnToShowMode();
    } else {
        turnToModifyMode();
    }
    initPageTurner(batches.length);
}

function generateContent(cell) {
    var content = cell["content"];
    if (cell["attributes"]["unit"] !== null && cell["attributes"]["unit"] !== undefined && cell["attributes"]["unit"] !== "") {
        content += cell["attributes"]["unit"];
    }
    return content;
}

function generateLabel(cell, factor) {
    var label = factor;
    if (cell["attributes"]["unit"] !== null && cell["attributes"]["unit"] !== undefined && cell["attributes"]["unit"] !== "") {
        label += "（" + cell["attributes"]["unit"] + "）";
    }
    return label;
}

function initPageTurner(pages) {
    CurrentPageNumber = pages;

    var html = "<li id=\"prev_page_btn\" class=\"waves-effect\"><a><i class=\"material-icons\">chevron_left</i></a></li>\n";
    for (var i = 0; i !== pages; ++i) {
        var page = i + 1;
        html += "<li id=\"page_" + page + "_btn\" class=\"waves-effect\"><a>" + page + "</a></li>\n"
    }
    html += "<li id=\"next_page_btn\" class=\"waves-effect\"><a><i class=\"material-icons\">chevron_right</i></a></li>\n";
    $(".pagination").html(html).on('click', 'li', function(e) {
        var target = $(e.currentTarget);
        if (target.hasClass('active') || target.hasClass('disabled')) {
            return;
        }
        if (target.attr('id') === "prev_page_btn") {
            turnToPage(Number(CurrentPage) - 1);
        } else if (target.attr('id') === "next_page_btn") {
            turnToPage(Number(CurrentPage) + 1);
        } else {
            turnToPage(target.text());
        }
    });
}

function turnToPage(page) {
    page = Number(page);
    if (CurrentPage !== 0) {
        $('#page_' + CurrentPage).hide();
        $('#page_' + CurrentPage + '_btn').removeClass('active').addClass('waves-effect');
    }
    if (CurrentPage === 1) {
        $('#prev_page_btn').removeClass('disabled').addClass('waves-effect');
    }
    if (CurrentPage === CurrentPageNumber) {
        $('#next_page_btn').removeClass('disabled').addClass('waves-effect');
    }

    CurrentPage = page;
    $('#page_' + CurrentPage + '_btn').removeClass('waves-effect').addClass('active');
    $('#page_' + CurrentPage).show();
    if (CurrentPage === 1) {
        $('#prev_page_btn').removeClass('waves-effect').addClass('disabled');
    }
    if (CurrentPage === CurrentPageNumber) {
        $('#next_page_btn').removeClass('waves-effect').addClass('disabled');
    }
}

function getSubmitData() {
    var ret = [];
    for (var i = 0, j = batches.length; i !== j; ++i) {
        var batch = batches[i];
        var thisCells = [];
        for (var p = 0, q = batch.length; p !== q; ++p) {
            thisCells.push(batch[p]["content"]);
        }
        ret.push(thisCells);
    }
    return ret;
}
