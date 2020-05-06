function randInt(a,b){
	return Math.trunc(a+(b-a)*Math.random());
}

class Culoare{
	constructor(_r = 0, _g = 0, _b = 0){
		this.r=_r;
		this.g = _g;
		this.b = _b;
	}
	generateRandom(){
		this.r = randInt(0, 256);
		this.g = randInt(0, 256);
		this.b = randInt(0, 256);
	}
	
	toString(){
		return "rgb("+this.r+","+this.g+","+this.b+")";
	}
	invert(){
		return new Culoare(255 - this.r, 255 - this.g, 255 - this.b);
	}
};

function ransom(sir)
{
	document.body.style.background = "grey";
	var scrisorica= document.getElementById("scrisorica");
	scrisorica.style.backgroundImage= "url('http://irinaciocan.ro/imagini/hartie_veche.png')";
	for (let i=0;i<sir.length;i++)
		{

			var patt1=/\s/g;

			if(!sir[i].match(patt1)) //verific spatiu
			{
				lit=document.createElement("span");
				scrisorica.appendChild(lit);
				lit.innerHTML= sir[i]; //litera i
				c=new Culoare();
				c.generateRandom();
				lit.style.color=c.toString();
				lit.style.background=c.invert().toString();
				lit.style.fontSize=randInt(20,31)+"px";
				nr=randInt(0,2);
				lit.style.fontWeight=(nr%2==0?"bold":"normal")
				nr=randInt(0,2);
				lit.style.fontStyle= (nr%2==0 ? "italic" : "normal");
				fonturi=["Times New Roman","Comic Sans MS","Impact","Arial Black","Courier New","Lucida Console","Trebuchet MS"];
				lit.style.fontFamily= fonturi[randInt(0,fonturi.length)];
				lit.onclick= function(){
					console.log(this.style.color + " " + this.style.background);
				}
			}
			else
			{
				scrisorica.appendChild(document.createTextNode(" ")); // pentru spatii nu mai facem span
			}
		}
}