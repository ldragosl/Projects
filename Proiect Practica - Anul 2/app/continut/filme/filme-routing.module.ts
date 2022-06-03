import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { PaginafilmeComponent } from './paginafilme/paginafilme.component';

const routes: Routes = [{
  path:'',
  component: PaginafilmeComponent
}];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class FilmeRoutingModule { }
