
window.onload = function()
{
	var v={
		"tastatura": "Instrument de percutie destinat enervarii colegilor de birou",
		"mouse": "Soarece mecanic fara blana care chitaie doar daca e stricat si are rolul de a misca o sagetica pe ecran",
		"casti": "Dispozitiv de acoperire a urechilor care inlocuieste zgomotul de fundal de birou cu o muzica placuta",
		"unitatea centrala": "Cutie metalica grea dar cu continut fragil"
	};
	var titlu = document.createElement("h2");	//creez titlul
	titlu.innerHTML = "Dictionar";		//ii dau valoarea 
	document.body.appendChild(titlu);	//adaug titlu
	var dlist = document.createElement("dl");	//creez tagul dl in document
	for(var key in v)
	{
		let dt1 = document.createElement("dt");	//creez tagul dt in interiorul tagului dl
		let dfn1 = document.createElement("dfn");	//creez tagul dfn in interiorul tagului dt
		dfn1.innerHTML = key;	//ii dau valoarea cheii lui dfn
		dt1.appendChild(dfn1);		//in dt pun dfn
		dlist.appendChild(dt1);		//in dl adaug dl
		let dd1 = document.createElement("dd");	//in dl creez dd
		dd1.innerHTML = v[key];	//ii dau valoarea cheii de pe pozitia i (definitia)
		dlist.appendChild(dd1);	//adaug la dl pe dd
	}
	document.body.appendChild(dlist);	//adaug lista de definitii la document

	var titluLista = document.createElement("h2"); 	//creez titlul pentru lista
	titluLista.innerHTML = "Undefined";	//ii dau valoarea corespunzatoare
	document.body.appendChild(titluLista);	//il adaug la document

	var ulist = document.createElement("ul");	//creez lista de nedefinite
	var paragraf = document.getElementsByClassName("pc");	//iau din document primul paragraf
	for(i = 0; i < paragraf.length; i++)	//verific daca fiecare cuvant se afla in dictionar
	{ 
		var ok = 1;
		for(var key in v)
		{
			if(paragraf[i].innerHTML.search(key) != -1)	//daca se afla in dictionar
			{
				ok = 0;
			}
		}
		if(ok)
		{
			let lis = document.createElement("li");	//creez un li 
			lis.innerHTML = paragraf[i].innerHTML;	//ii dau valoarea cuvantului negasit
			ulist.appendChild(lis);	//il adaug la lista
		}
	}
	document.body.appendChild(ulist);	//adaug lista la document
}

