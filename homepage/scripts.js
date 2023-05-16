// Show and Hide function
function hideOrNot(idinfo) {
    var element = document.getElementById(idinfo);
    if (element.style.display === "none") {
        element.style.display = "flex";
    } else {
        element.style.display = "none";
    }
}
