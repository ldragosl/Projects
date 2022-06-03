import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { SelectorPaginaComponent } from './selector-pagina/selector-pagina.component';
import {MatDividerModule} from '@angular/material/divider';
import { MatButtonModule } from '@angular/material/button';
import { ReviewComponent } from './review/review.component';
import { MatIconModule } from '@angular/material/icon';


@NgModule({
  declarations: [
    SelectorPaginaComponent,
    ReviewComponent
  ],
  exports:[
    SelectorPaginaComponent,
    ReviewComponent
  ],
  imports: [
    CommonModule,
    MatDividerModule,
    MatButtonModule,
    MatIconModule
  ]
})
export class ObiectePersistenteModule { }
