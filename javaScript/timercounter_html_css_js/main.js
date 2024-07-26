
let countLabel = document.getElementById("num");
let inc_btn = document.getElementById("increase");
let dic_btn = document.getElementById("decrease");
let res_btn = document.getElementById("reset");

let count = 0;
countLabel.textContent = 0;


inc_btn.onclick = function(){
    count++;
    countLabel.textContent= count;
}

dic_btn.onclick = function(){
    count--;
    countLabel.textContent= count;
}

res_btn.onclick = function(){
    count = 0;
    countLabel.textContent = count;
}
