var interface = null;

$(document).ready(function() {
    $('#loader').hide();

    new QWebChannel(qt.webChannelTransport, function (channel) {
        interface = channel.objects.VEDAInitOperationDialogInterface;

        $('#select_save_path_btn').click(function () {
            interface.onSelectSavePathBtnClicked();
        });
    });
});

function setPath(path) {
    $('#save_path').val(path);
}
