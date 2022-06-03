import { Injectable } from '@angular/core';
import { Subject } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class ServiciuSelectorSortareService {

  constructor() { }

  comunicare =  new Subject<number>();

  comunica(valoare: number){
    this.comunicare.next(valoare);
  }
}
