window.onload=function(){

	document.getElementById("albastreste").onclick = function()
	{
		pgfs = document.querySelectorAll("p")
		for(let i = 0; i < pgfs.length; i++)
		{
			var culoare = window.getComputedStyle(pgfs[i]).getPropertyValue("color");
			if(culoare == "rgb(255, 0, 0)")
				pgfs[i].style.color = "blue"
		} 
	}
}

function albastreste(){
	pgfs=document.querySelectorAll("p");
	
	//de observat si apoi de comentat
	alert(pgfs[0].style.color)
	pgfs[0].style.color="blue"
	alert(pgfs[0].style.color)
}