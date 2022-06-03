import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class ServiciuLogareService {

  constructor() { }

  esteLogat():boolean{
    var rezultat: any = window.sessionStorage.getItem('logat');
    if(rezultat == null)
      return false;
    else if(rezultat == 'true')
      return true;
    else return false;
  }

  loginAutomat(){
    var email:any = window.localStorage.getItem('numeRetinut');
    var parola:any = window.localStorage.getItem('parolaRetinuta');
    if(email == null || parola == null)
      return;
    if(window.localStorage.getItem(email) == parola){
      window.sessionStorage.setItem('logat', 'true');
    }
  }

  login(email:string, parola:string, tineMinte:boolean):boolean{
    if(window.localStorage.getItem(email) == parola){
      window.sessionStorage.setItem('logat', 'true');
      if(tineMinte == true){
        window.localStorage.setItem('numeRetinut', email);
        window.localStorage.setItem('parolaRetinuta', parola);
      }
      return true;
    }
    else return false;
  }

  inregistrare(email:string, parola:string){
    window.localStorage.setItem(email, parola);
  }

  static verificareExistenta(email:string):boolean{
    if(window.localStorage.getItem(email) != null)
      return true;
    return false;
  }
}
