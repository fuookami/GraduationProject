var interface = null;

$(document).ready(function() {
    $('#loader').hide();

    new QWebChannel(qt.webChannelTransport, function (channel) {
        interface = channel.objects.VEDAInitProjectDialogInterface;

        $('#select_save_path_btn').click(function() {
            interface.onSelectSavePathBtnClicked();
        });

        $('#confirm_btn').click(function() {
            var name = $('#project_name');
            var save_path = $('#save_path');

            if (name.val() !== "" && name.hasClass('valid') && save_path.val() !== "") {
                setLoading(true);
                interface.onConfirmBtnClicked(name.val(), save_path.val(), $('#init_new_dir').prop('checked'));
            } else {
                $('#information').html("实验项目名称和实验项目保存位置均不能为空。");
            }
        });

        $('#cancel_btn').click(function() {
            interface.onCancelBtnClicked();
        });

        interface.savePathSelected.connect(function(path) {
            $('#save_path').val(path);
        });

        interface.initProjectFailed.connect(function(info) {
            setLoading(false);

            $('#information').html(info);
        });
    });
});
