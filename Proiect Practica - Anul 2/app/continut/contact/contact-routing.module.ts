import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { PaginaContactComponent } from './pagina-contact/pagina-contact.component';

const routes: Routes = [
  {
    path:'',
    component:PaginaContactComponent
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class ContactRoutingModule { }
