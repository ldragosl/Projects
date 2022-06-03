import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { AuthPostLoginGuard } from './guards/auth-post-login.guard';
import { AuthPreLoginGuard } from './guards/auth-pre-login.guard';

const routes: Routes = [
  {
    path: 'login',
    canActivate: [AuthPostLoginGuard],
    loadChildren: () => import('./account/login/login.module').then(m => m.LoginModule)
  },
  {
    path: 'inregistrare',
    canActivate: [AuthPostLoginGuard],
    loadChildren: () => import('./account/inregistrare/inregistrare.module').then(m => m.InregistrareModule)
  },
  {
    path: 'filme',
    canActivate: [AuthPreLoginGuard],
    loadChildren: () => import('./continut/filme/filme.module').then(m => m.FilmeModule)
  },
  {
    path: 'contact',
    canActivate: [AuthPreLoginGuard],
    loadChildren: () => import('./continut/contact/contact.module').then(m => m.ContactModule)
  },
  {
    path: 'legal',
    loadChildren: () => import('./continut/legal/legal.module').then(m => m.LegalModule)
  },
  {
    path: '',
    canActivate: [AuthPreLoginGuard],
    loadChildren: () => import('./continut/home/home.module').then(m => m.HomeModule)
  },
  {
    path: '**',
    canActivate: [AuthPreLoginGuard],
    loadChildren: () => import('./continut/home/home.module').then(m => m.HomeModule)
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
