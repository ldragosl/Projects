import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormControl, FormGroup, Validators } from '@angular/forms';
import { Router } from '@angular/router';
import { ServiciuLogareService } from 'src/app/servicii/serviciu-logare.service';
import { ValidatoriCustom } from 'src/app/utilitati/validatori-custom';

@Component({
  selector: 'app-loginpage',
  templateUrl: './loginpage.component.html',
  styleUrls: ['./loginpage.component.scss', '../../../app.component.scss']
})
export class LoginpageComponent implements OnInit {
  constructor(private formBuilder : FormBuilder, private router:Router, private serviciuLogare:ServiciuLogareService) { }

  formLogin!:FormGroup;

  ngOnInit(): void {
    this.formLogin = this.formBuilder.group({
      username: ['', Validators.compose([Validators.required, Validators.email])],
      parola:  ['', Validators.compose([Validators.minLength(6), Validators.required, ValidatoriCustom.parolaPuternica()])]
    })
  }

  tineMinte = new FormControl('');

  login(){
    if(this.serviciuLogare.login(this.formLogin.get('username')?.value, this.formLogin.get('parola')?.value, this.tineMinte.value)){
      this.router.navigate(['/']);
    }
  }
  inregistrare(){
    this.router.navigate(['inregistrare']);
  }

  obtineEroareEmail(){
    if (this.formLogin.get('username')?.hasError('required')) {
      return 'Completeaza acest camp';
    }
    if(this.formLogin.get('username')?.hasError('email')){
      return 'Adresa email invalida'
    }

    return 'Eroare necunoscuta';
  }
  obtineEroareParola(){
    if(this.formLogin.get('parola')?.hasError('required')) {
      return 'Completeaza acest camp';
    }
    if(this.formLogin.get('parola')?.hasError('minlength')){
      return 'Introdu minim 6 caractere'
    }
    if(this.formLogin.get('parola')?.hasError('parolaPuternica')){
      return 'Parola nu e suficient de puternica';
    }

    return 'Eroare necunoscuta';
  }
}
