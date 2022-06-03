import { AbstractControl, ValidationErrors, ValidatorFn } from "@angular/forms";
import { RegisterpageComponent } from "../account/inregistrare/registerpage/registerpage.component";
import { ServiciuLogareService } from "../servicii/serviciu-logare.service";

export class ValidatoriCustom{
    static parolaPuternica():ValidatorFn{
        return (control: AbstractControl): ValidationErrors | null =>{
            const value = control.value;

            if(!value)
                return null;
            const areLiteraMare = /[A-Z]+/.test(value);
            const areLiteraMica = /[a-z]+/.test(value);
            const areNumar = /[0-9]+/.test(value);
            const areSpecial = /(?=.*[!@#$%^&*])/.test(value);

            return !(areLiteraMare && areLiteraMica && areNumar && areSpecial) ? {parolaPuternica: "true"} : null;
        }
    }
    static parolaConfirmata(compInregistrare: RegisterpageComponent):ValidatorFn{
        return (control: AbstractControl): ValidationErrors | null =>{
            if(compInregistrare == null || compInregistrare.formInregistrare == null)
                return null;

            if(compInregistrare.formInregistrare.get('parola')?.value != compInregistrare.formInregistrare.get('confirmaParola')?.value){
                return {parolaConfirmata: 'false'};
            }
            return null;
        }
    }
    static verificareInjectii():ValidatorFn{
        return (control: AbstractControl): ValidationErrors | null =>{
            if(control.value == 'numeRetinut' || control.value == 'parolaRetinuta' || control.value == 'filme')
                return {numeInvalid:'true'};
            return null;
        }
    }
    static verificareDuplicat():ValidatorFn{
        return (control: AbstractControl): ValidationErrors | null =>{
            if(ServiciuLogareService.verificareExistenta(control.value)){
                return {dejaExista:'true'}
            }
            return null;
        }
    }
}