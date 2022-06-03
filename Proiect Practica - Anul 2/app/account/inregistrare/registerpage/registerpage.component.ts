import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { Router } from '@angular/router';
import { ServiciuLogareService } from 'src/app/servicii/serviciu-logare.service';
import { ValidatoriCustom } from 'src/app/utilitati/validatori-custom';

@Component({
  selector: 'app-registerpage',
  templateUrl: './registerpage.component.html',
  styleUrls: ['./registerpage.component.scss', '../../../app.component.scss']
})
export class RegisterpageComponent implements OnInit {
  constructor(private formBuilder : FormBuilder, private router:Router, private serviciuLogare:ServiciuLogareService) { }

  formInregistrare!:FormGroup;

  ngOnInit(): void {
    this.formInregistrare = this.formBuilder.group({
      username: ['', Validators.required],
      email: ['', Validators.compose([Validators.required, Validators.email, ValidatoriCustom.verificareInjectii(), ValidatoriCustom.verificareDuplicat()])],
      parola:  ['', Validators.compose([Validators.minLength(6), Validators.required, ValidatoriCustom.parolaPuternica()])],
      confirmaParola: ['', Validators.compose([Validators.required, ValidatoriCustom.parolaConfirmata(this)])],
      termeni: ['', Validators.requiredTrue]
    })
  }

  login(){
    this.router.navigate(['/login']);
  }
  inregistrare(){
    this.serviciuLogare.inregistrare(this.formInregistrare.get('email')?.value, this.formInregistrare.get('parola')?.value);
    this.router.navigate(['/login']);
  }

  obtineEroareEmail(){
    if (this.formInregistrare.get('email')?.hasError('required')) {
      return 'Completeaza acest camp';
    }
    if(this.formInregistrare.get('email')?.hasError('email')){
      return 'Adresa email invalida';
    }
    if(this.formInregistrare.get('email')?.hasError('numeInvalid')){
      return 'Acest nume e invalid';
    }
    if(this.formInregistrare.get('email')?.hasError('dejaExista')){
      return 'Emailul e deja utilizat';
    }
    return 'Eroare necunoscuta';
  }
  obtineEroareParola(){
    if(this.formInregistrare.get('parola')?.hasError('required')) {
      return 'Completeaza acest camp';
    }
    if(this.formInregistrare.get('parola')?.hasError('minlength')){
      return 'Introdu minim 6 caractere';
    }
    if(this.formInregistrare.get('parola')?.hasError('parolaPuternica')){
      return 'Parola nu e suficient de puternica';
    }

    return 'Eroare necunoscuta';
  }

  obtineEraoreConfirmaParola(){
    if(this.formInregistrare.get('confirmaParola')?.hasError('required')) {
      return 'Completeaza acest camp';
    }
    if(this.formInregistrare.get('confirmaParola')?.hasError('parolaConfirmata')) {
      return 'Acest camp trebuie sa fie identic cu parola';
    }

    return 'Eroare necunoscuta';
  }
  obtineEroareUsername(){
    if(this.formInregistrare.get('username')?.hasError('required')) {
      return 'Completeaza acest camp';
    }

    return 'Eroare necunoscuta';
  }
}
