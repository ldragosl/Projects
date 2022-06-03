import { Injectable } from '@angular/core';
import { ActivatedRouteSnapshot, CanActivate, Router, RouterStateSnapshot, UrlTree } from '@angular/router';
import { Observable } from 'rxjs';
import { ServiciuLogareService } from '../servicii/serviciu-logare.service';

@Injectable({
  providedIn: 'root'
})
export class AuthPostLoginGuard implements CanActivate {
  constructor(private serviciuLogare:ServiciuLogareService, private router: Router){
  }
  canActivate(
    route: ActivatedRouteSnapshot,
    state: RouterStateSnapshot): Observable<boolean | UrlTree> | Promise<boolean | UrlTree> | boolean | UrlTree {
      if(!this.serviciuLogare.esteLogat())
        return true;
      else{
        this.router.navigate(['']);
        return false;
      }
  }
  
}
