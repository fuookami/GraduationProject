var interface = null;

$(document).ready(function(){
    new QWebChannel(qt.webChannelTransport, function (channel) {
        interface = channel.objects.VEDAAboutDialogInterface;

        $('#confirm_btn').click(function(){
            interface.onConfirmBtnClicked();
        });

        $('#github_btn').click(function(){
            interface.onGithubBtnClicked();
        });

        $('#coding_btn').click(function(){
            interface.onCodingBtnClicked();
        });
    });
});

function setInfo(version, buildDatetime) {
    $('#Version').html(version);
    $('#BuildDatetime').html(buildDatetime);
}
