window.onload = function()
{
    var semafor = 1;
    document.getElementById("inversareDOM").onclick = function()
    {
        var newL = document.getElementById("lista");
        var elem = newL.getElementsByTagName("li");
        var i = elem.length - 1;
        while(i >= 0)
        {
            newL.appendChild(elem[i]);
            i--;
        }
    }
    //folosind list.reversed = true se schimba doar indicii listei, ordinea elementelor ramane aceeasi
    document.getElementById("reversed").onclick = function()
    {
        if(semafor == 1)
        {
            document.getElementById("lista").reversed = true;
            semafor = 0;
        }
        else
        {
            document.getElementById("lista").reversed = false;
            semafor = 1;
        }
    }
}