import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { LegalPageComponent } from './legal-page/legal-page.component';

const routes: Routes = [{
  path:'',
  component:LegalPageComponent
}];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class LegalRoutingModule { }
