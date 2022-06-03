import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { LegalRoutingModule } from './legal-routing.module';
import { LegalPageComponent } from './legal-page/legal-page.component';
import { MatCardModule } from '@angular/material/card';
import { ObiectePersistenteModule } from '../obiecte-persistente/obiecte-persistente.module';


@NgModule({
  declarations: [
    LegalPageComponent
  ],
  imports: [
    CommonModule,
    LegalRoutingModule,
    MatCardModule,
    ObiectePersistenteModule
  ]
})
export class LegalModule { }
