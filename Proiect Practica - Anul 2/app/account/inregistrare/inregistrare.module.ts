import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { InregistrareRoutingModule } from './inregistrare-routing.module';
import { RegisterpageComponent } from './registerpage/registerpage.component';
import { ReactiveFormsModule } from '@angular/forms';
import { MatButtonModule } from '@angular/material/button';
import { MatCardModule } from '@angular/material/card';
import { MatCheckboxModule } from '@angular/material/checkbox';
import { MatFormFieldModule } from '@angular/material/form-field';
import { MatInputModule } from '@angular/material/input';


@NgModule({
  declarations: [
    RegisterpageComponent
  ],
  imports: [
    CommonModule,
    InregistrareRoutingModule,
    ReactiveFormsModule,
    MatFormFieldModule,
    MatButtonModule,
    MatInputModule,
    MatCheckboxModule,
    MatCardModule
  ]
})
export class InregistrareModule { }
