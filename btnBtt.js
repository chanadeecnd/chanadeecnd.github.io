let btn = document.getElementById('btt');
function scroll() {
    if (document.body.scrollTop > 200 || document.documentElement.scrollTop > 200) {
        btn.style.display = 'block'
    } else {
        btn.style.display = 'none'
    }
}

function backToTop() {
    document.documentElement.scrollTop = 0;
    document.body.scrollTop = 0;
}

window.onscroll = function () {
    scroll()
}