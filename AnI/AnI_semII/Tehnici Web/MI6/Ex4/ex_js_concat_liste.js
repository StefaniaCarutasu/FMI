function concatListe()
{
    var destinatie = document.getElementById("lista1");
    var sursa = document.getElementById("lista2").children;
    for(i = 0; i < sursa.length; i++)
    {
        var li = sursa[i];
        destinatie.appendChild(li);
        i--;
    }
}