import { Component } from '@angular/core';
import {MatBottomSheetRef} from '@angular/material/bottom-sheet';
import { ServiciuSelectorSortareService } from 'src/app/servicii/serviciu-selector-sortare.service';

@Component({
    selector: 'selector-sortare',
    templateUrl: './selector-sortare.html',
  })
  export class SelectorSortare {
    constructor(private bottomSheetRef: MatBottomSheetRef<SelectorSortare>, private comunicare:ServiciuSelectorSortareService) {}

    ordonare(valoare:number){
        this.bottomSheetRef.dismiss();
        this.comunicare.comunica(valoare);
    }
  }