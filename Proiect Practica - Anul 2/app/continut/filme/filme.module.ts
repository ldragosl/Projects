import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { FilmeRoutingModule } from './filme-routing.module';
import { PaginafilmeComponent } from './paginafilme/paginafilme.component'
import { ObiectePersistenteModule } from '../obiecte-persistente/obiecte-persistente.module';
import { MatFormFieldModule } from '@angular/material/form-field';
import { MatInputModule } from '@angular/material/input';
import {MatCardModule} from '@angular/material/card';
import {MatDividerModule} from '@angular/material/divider';
import { MatButtonModule } from '@angular/material/button';
import {ReactiveFormsModule } from '@angular/forms';
import {MatIconModule} from '@angular/material/icon';
import { MatBottomSheetModule } from '@angular/material/bottom-sheet';
import {MatListModule} from '@angular/material/list';
import { SelectorSortare } from './paginafilme/selector/selector-sortare.component';


@NgModule({
  declarations: [
    PaginafilmeComponent,
    SelectorSortare
  ],
  imports: [
    CommonModule,
    FilmeRoutingModule,
    ObiectePersistenteModule,
    MatFormFieldModule,
    MatInputModule,
    MatCardModule,
    MatDividerModule,
    MatButtonModule,
    ReactiveFormsModule,
    MatIconModule,
    MatBottomSheetModule,
    MatListModule
  ]
})
export class FilmeModule { }
