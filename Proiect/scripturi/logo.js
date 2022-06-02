//incarcare logo
let request = new XMLHttpRequest();
request.onreadystatechange=function(){
    if(this.readyState==4&&this.status==200){
        const divSVG = document.getElementById("div-logo");
        if(divSVG != null){
            //alert("am primit raspuns");
            const nsSVG="http://www.w3.org/2000/svg";
            let svgLogo=document.createElementNS(nsSVG, "svg");
            svgLogo.setAttribute("width",40);
            svgLogo.setAttribute("height",40);
            svgLogo.setAttribute("id", "logo");
            let linieLogo=document.createElementNS(nsSVG, "polyline");
            let puncte = this.responseXML.getElementsByTagName("point")
            let str = "";
            for(let i=0;i<puncte.length;i++){
                str+=puncte[i].getElementsByTagName("x")[0].firstChild.nodeValue*2+","+puncte[i].getElementsByTagName("y")[0].firstChild.nodeValue*2+" ";
            }
            linieLogo.setAttribute("points", str);

            linieLogo.setAttribute("class", "linie-logo");
            svgLogo.append(linieLogo);
            divSVG.append(svgLogo);
        }
    }
};
//se incarca sincron pentru ca altfel devine observabila incarcarea logo-ului (se misca anumite elemente)
request.open("GET", "https://mgx17.github.io/AJAX/input.xml", false);//placeholder
request.send();