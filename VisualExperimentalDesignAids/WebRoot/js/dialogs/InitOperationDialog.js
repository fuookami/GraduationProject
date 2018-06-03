var interface = null;
var curr_method_name = "";
var curr_method_category = "";
var curr_attribute_names = [];
var curr_attribute_displays = [];

$(document).ready(function() {
    $(document).bind("contextmenu",function(e){
        return false;
    });

    $('#method_category_box').hide();
    $('#attribute_box').hide();

    $('#loader').hide();
    $('select').material_select();

    new QWebChannel(qt.webChannelTransport, function (channel) {
        interface = channel.objects.VEDAInitOperationDialogInterface;

        $('#select_save_path_btn').click(function () {
            interface.onSelectSavePathBtnClicked();
        });

        $('#method_name').on('change', function(){
            var method_name = $('#method_name').val();
            if (method_name !== curr_method_name) {
                curr_method_name = method_name;

                setLoading(true);
                interface.onCategoryRequested(curr_method_name);
            }
        });

        $('#method_category').on('change', function(){
            var method_category = $('#method_category').val();
            if (method_category !== curr_method_category) {
                curr_method_category = method_category;

                setLoading(true);
                interface.onAttributeRequested(curr_method_name, curr_method_category);
            }
        });

        $('#confirm_btn').click(function() {
            var name = $('#operation_name');
            var save_path = $('#save_path');
            var method_name = $('#method_name');
            var method_category = $('#method_category');

            if (name.val() !== "" && !name.hasClass('invalid')
                && save_path.val() !== "" && !save_path.hasClass('invalid')) {

                if (method_name.val() !== "" && method_category !== "") {
                    var valid = true;
                    for (var i = 0, j = curr_attribute_names.length; i !== j; ++i) {
                        var curr_attribute = $('#' + curr_attribute_names[i]);
                        if (curr_attribute.attr('type') === "number") {
                            if (curr_attribute.val() === "") {
                                $('#information').html(curr_attribute_displays[i] + "不能为空");
                                valid = false;
                                break;
                            } else if (isNaN(curr_attribute.val())) {
                                $('#information').html(curr_attribute_displays[i] + "不是一个有效的实数值");
                                valid = false;
                                break;
                            }
                        }
                    }

                    if (valid) {
                        var attribute = {};
                        for (var i = 0, j = curr_attribute_names.length; i !== j; ++i) {
                            var curr_attribute = $('#' + curr_attribute_names[i]);
                            if (curr_attribute.attr('type') === "checkbox") {
                                attribute[curr_attribute_names[i]] = curr_attribute.prop('checked') ? "true" : "false";
                            } else if (curr_attribute.attr('type') === "number") {
                                attribute[curr_attribute_names[i]] = curr_attribute.val().toString();
                            } else {
                                attribute[curr_attribute_names[i]] = curr_attribute.val();
                            }
                        }

                        interface.onConfirmBtnClicked(name.val(), save_path.val(), $('#init_new_dir').prop('checked'), method_name.val(), method_category.val(), JSON.stringify(attribute));
                    }
                } else {
                    $('#information').html("必须选择实验设计方法及其类别");
                }
            } else {
                $('#information').html("实验操作名称和实验操作保存位置均不能为空。");
            }
        });

        $('#cancel_btn').click(function(){
            interface.onCancelBtnClicked();
        });

        interface.methodResponce.connect(function(data) {
            setLoading(false);
            refreshMethods($.parseJSON(data));
        });

        interface.categoryResponce.connect(function(data) {
            setLoading(false);
            refreshCategories($.parseJSON(data));
        });

        interface.attributeResponce.connect(function(data) {
            setLoading(false);
            refreshAttributes($.parseJSON(data));
        });

        setLoading(true);
        interface.onMethodRequested();
    });
});

function setPath(path) {
    $('#save_path').val(path);
}

function refreshMethods(methods) {
    var html5 = '<option value="" disabled selected>选择实验设计方法</option>';
    for (var key in methods) {
        html5 += '<option value="' + key + '">' + methods[key] + '</option>';
    }

    $('#method_name').html(html5).material_select();
}

function refreshCategories(categories) {
    var html5 = '<option value="" disabled selected>选择实验设计方法类别</option>';
    for (var key in categories) {
        html5 += '<option value="' + key + '">' + categories[key] + '</option>';
    }

    $('#method_category_box').show();
    $('#method_category').html(html5).material_select();
}

function refreshAttributes(attributes) {
    var html5 = '';
    curr_attribute_names = [];

    for (var name in attributes) {
        var type = attributes[name]["type"];
        var display = attributes[name]["name"];

        curr_attribute_names.push(name);
        curr_attribute_displays.push(display);

        var input_type =
            type === "Boolean" ? "checkbox"
            : type === "Number" ? "number"
                : type === "String" ? "text" : "text";

        if (input_type === "checkbox") {
            html5 +=
                '            <p class="col s12">\n' +
                '                <input id="' + name + '" type="' + input_type + '" class="filled-in" />\n' +
                '                <label for="' + name + '">' + display + '</label>\n' +
                '            </p>';
        } else {
            html5 +=
                '            <div class="col s12 input-field">\n' +
                '                <input id="' + name + '" type="' + input_type + '" class="filled-in"/>\n' +
                '                <label for="' + name + '">' + display + '</label>\n' +
                '            </div>';
        }
    }

    $('#attribute_box').html(html5).show();
    Materialize.updateTextFields();
}
