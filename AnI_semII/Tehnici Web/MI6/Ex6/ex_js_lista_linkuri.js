window.onload = function(){
    var ok = -1;
    document.getElementById("schimba").onclick = function()
    {
        var newL = document.getElementById("linkuri").children;
        var i = 0;
        while(i < newL.length)
        {
            if(ok == 1)
                var newElem = document.createTextNode(newL[i].childNodes[0].innerHTML);
            else
            {
                var newElem = document.createElement("a");
                newElem.href = newL[i].innerHTML;
                newElem.target = "_blank";
                newElem.innerHTML = newL[i].innerHTML;
            }
            newL[i].replaceChild(newElem, newL[i].childNodes[0]);
            i++;
        }
        ok *= -1;
    }
}