import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { ContinutFilmService } from 'src/app/servicii/continut-film.service';
import { ContactModule } from '../contact.module';

@Component({
  selector: 'app-pagina-contact',
  templateUrl: './pagina-contact.component.html',
  styleUrls: ['./pagina-contact.component.scss']
})
export class PaginaContactComponent implements OnInit {

  constructor(private formBuilder: FormBuilder, private continutFilm:ContinutFilmService) { }

  formGeneral!:FormGroup;
  formDetalii!:FormGroup;
  formDescriere!:FormGroup;

  formFinalizat(){
    this.continutFilm.salveazaFilm(
      this.formGeneral.get('campNume')?.value, 
      this.formDetalii.get('campRegizor')?.value, 
      this.formDetalii.get('campDurataMinute')?.value, 
      this.formDetalii.get('campAn')?.value, 
      this.formDescriere.get('campDescriere')?.value, 
    );
  }

  ngOnInit(): void {
    this.formGeneral = this.formBuilder.group({
      campNume: ['', Validators.required],
    });
    this.formDetalii = this.formBuilder.group({
      campRegizor: ['', Validators.required],
      campAn: ['', Validators.required],
      campDurataMinute: ['', Validators.required],
    });
    this.formDescriere = this.formBuilder.group({
      campDescriere: ['', Validators.required],
    });
  }

}
