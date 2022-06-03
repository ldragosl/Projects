import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { ContactRoutingModule } from './contact-routing.module';
import { PaginaContactComponent } from './pagina-contact/pagina-contact.component';
import { ObiectePersistenteModule } from '../obiecte-persistente/obiecte-persistente.module';
import {MatStepperModule} from '@angular/material/stepper';
import { ReactiveFormsModule } from '@angular/forms';
import { MatButtonModule } from '@angular/material/button';
import { MatFormFieldModule } from '@angular/material/form-field';
import { MatInputModule } from '@angular/material/input';


@NgModule({
  declarations: [
    PaginaContactComponent
  ],
  imports: [
    CommonModule,
    ContactRoutingModule,
    ObiectePersistenteModule,
    MatStepperModule,
    ReactiveFormsModule,
    MatFormFieldModule,
    MatButtonModule,
    MatInputModule,
  ]
})
export class ContactModule { }
