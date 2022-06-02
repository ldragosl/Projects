document.getElementById("telefon").value = window.sessionStorage.getItem("telefonRetinut");
document.getElementById("email").value = window.sessionStorage.getItem("emailRetinut");
document.getElementById("prenume").value = window.sessionStorage.getItem("prenumeRetinut");
document.getElementById("nume").value = window.sessionStorage.getItem("numeRetinut");
document.getElementById("adresa").value = window.sessionStorage.getItem("adresaRetinuta");
document.getElementById("mesaj").value = window.sessionStorage.getItem("mesaj");

if(window.sessionStorage.getItem("mesajTrimis") != null){
    window.sessionStorage.removeItem("mesajTrimis");
    let divSucces = document.getElementById("mesaj-trimis");
    divSucces.innerHTML="<p style=\"color:green;font-size:20px;\">Mesaj trimis cu succes!</p>";
}

function contact(){
    window.sessionStorage["telefonRetinut"]=document.getElementById("telefon").value;
    window.sessionStorage["emailRetinut"]=document.getElementById("email").value;
    window.sessionStorage["prenumeRetinut"]=document.getElementById("prenume").value;
    window.sessionStorage["numeRetinut"]=document.getElementById("nume").value;
    window.sessionStorage["adresaRetinuta"]=document.getElementById("adresa").value;

    if(document.getElementById("prenume").value != "" && document.getElementById("nume").value != "" && document.getElementById("email").value != "" && document.getElementById("mesaj").value != ""){
        window.sessionStorage["mesajTrimis"]=true;
    }
}

function salvare(){
    window.sessionStorage["telefonRetinut"]=document.getElementById("telefon").value;
    window.sessionStorage["emailRetinut"]=document.getElementById("email").value;
    window.sessionStorage["prenumeRetinut"]=document.getElementById("prenume").value;
    window.sessionStorage["numeRetinut"]=document.getElementById("nume").value;
    window.sessionStorage["adresaRetinuta"]=document.getElementById("adresa").value;
    window.sessionStorage["mesaj"]=document.getElementById("mesaj").value;
}