function setVersion(version) {
    $('#Version').html("版本：" + version);
}

function setBuildDatetime(buildDatetime) {
    $('#BuildDatetime').html("软件生成日期：" + buildDatetime);
}

function showAbout() {
    $('#AboutDialog').modal('open');
}

function setLoading(loading) {
    if (loading) {
        $('#loader').show();
    } else {
        $('#loader').hide();
    }
}

function information(title, text) {
    $('#InformationTitle').html(title);
    $('#InformationText').html(text);

    $('#InformationDialog').modal('open');
}

function booleanSelect(title, text, todo1, todo2) {
    $('#BooleanSelectTitle').html(title);
    $('#BooleanSelectText').html(text);
    $('#boolean_select_btn1').click(function(){
        todo1();

        $('#boolean_select_btn1').unbind();
        $('#boolean_select_btn2').unbind();
    });

    $('#boolean_select_btn2').click(function(){
        todo2();

        $('#boolean_select_btn1').unbind();
        $('#boolean_select_btn2').unbind();
    });

    $('#BooleanSelectDialog').modal('open');
}

function comfirm(title, text, todo) {
    $('#ComfirmTitle').html(title);
    $('#ComfirmText').html(text);
    $('#comfirm_btn').click(function(){
        todo();

        $('#comfirm_btn').unbind();
    });

    $('#ComfirmDialog').modal('open');
}

function tricomfirm(title, text, btn1_text, todo1, btn2_text, todo2) {
    $('#TriComfirmTitle').html(title);
    $('#TriComfirmText').html(text);
    $('#tri_comfirm_btn1').html(btn1_text).click(function(){
        todo1();

        $('#tri_comfirm_btn1').unbind();
        $('#tri_comfirm_btn2').unbind();
    });
    $('#tri_comfirm_btn2').html(btn2_text).click(function(){
        todo2();

        $('#tri_comfirm_btn1').unbind();
        $('#tri_comfirm_btn2').unbind();
    });

    $('#TriComfirmDialog').modal('open');
}
