var interface = null;

$(document).ready(function() {
    $(document).bind("contextmenu",function(e){
        return false;
    });
    $('#loader').hide();

    new QWebChannel(qt.webChannelTransport, function (channel) {
        interface = channel.objects.VEDAInitModelDialogInterface;

        $('#select_save_path_btn').click(function() {
            interface.onSelectSavePathBtnClicked();
        });

        $('#confirm_btn').click(function() {
            var name = $('#data_name');
            var save_path = $('#save_path');

            if (name.val() !== "" && !name.hasClass('invalid')
                && save_path.val() !== "" && !save_path.hasClass('invalid')) {
                setLoading(true);
                interface.onConfirmBtnClicked(name.val(), save_path.val());
            } else {
                $('#information').html("实验数据名称和实验数据保存位置均不能为空。");
            }
        });

        $('#cancel_btn').click(function() {
            interface.onCancelBtnClicked();
        });

        interface.savePathSelected.connect(function(path) {
            $('#save_path').val(path);
        });

        interface.initDataFailed.connect(function(info) {
            setLoading(false);

            $('#information').html(info);
        });
    });
});

function setPath(path) {
    $('#save_path').val(path);
}
