var interface = null;

$(document).ready(function() {
    $(document).bind("contextmenu",function(e){
        return false;
    });
    $('#loader').hide();

    $('#init_model').on('change', function(){
        if ($('#init_model').prop('checked')) {
            $('#model_name_box').show();
        } else {
            $('#model_name_box').hide();
        }
    });

    new QWebChannel(qt.webChannelTransport, function (channel) {
        interface = channel.objects.VEDAInitProcessDialogInterface;

        $('#select_save_path_btn').click(function() {
            interface.onSelectSavePathBtnClicked();
        });

        $('#confirm_btn').click(function() {
            var name = $('#process_name');
            var save_path = $('#save_path');

            if (!$('#init_model').prop('checked')) {
                if (name.val() !== "" && !name.hasClass('invalid')
                    && save_path.val() !== "" && !save_path.hasClass('invalid')) {
                    setLoading(true);
                    interface.onConfirmBtnClicked(name.val(), save_path.val(), $('#init_new_dir').prop('checked'));
                } else {
                    $('#information').html("实验流程名称和实验流程保存位置均不能为空。");
                }
            } else {
                var model_name = $('#model_name');
                if (name.val() !== "" && !name.hasClass('invalid')
                    && save_path.val() !== "" && !save_path.hasClass('invalid')
                    && model_name.val() !== "" && !model_name.hasClass('invalid')) {
                    setLoading(true);
                    interface.onConfirmBtnClickedWithModel(name.val(), save_path.val(), $('#init_new_dir').prop('checked'), model_name.val());
                } else {
                    $('#information').html("实验流程名称、实验流程保存位置和实验因素数据模型名称均不能为空。");
                }
            }
        });

        $('#cancel_btn').click(function() {
            interface.onCancelBtnClicked();
        });

        interface.savePathSelected.connect(function(path) {
            $('#save_path').val(path);
        });

        interface.initProcessFailed.connect(function(info) {
            setLoading(false);

            $('#information').html(info);
        });
    });
});

function setPath(path) {
    $('#save_path').val(path);
}
