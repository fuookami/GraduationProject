$(document).ready(function() {
    initDropDowns();
    initDialogs();
});

function initDropDowns() {
    $(".dropdown-content").dropdown();
}

function initDialogs() {
    $(".modal").modal();
    $('#loader').hide();

    $('#about_btn').click(function(){
        $('#AboutDialog').modal('open');
    });
}
