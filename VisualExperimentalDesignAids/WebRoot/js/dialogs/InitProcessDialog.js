var interface = null;

$(document).ready(function() {
    $('#loader').hide();

    new QWebChannel(qt.webChannelTransport, function (channel) {
        interface = channel.objects.VEDAInitProcessDialogInterface;

        $('#select_save_path_btn').click(function() {
            interface.onSelectSavePathBtnClicked();
        });

        interface.savePathSelected.connect(function(path) {
            $('#save_path').val(path);
        });
    });
});

function setPath(path) {
    $('#save_path').val(path);
}
