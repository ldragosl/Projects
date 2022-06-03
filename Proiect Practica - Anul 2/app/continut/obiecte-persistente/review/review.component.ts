import { Component, Input, OnInit } from '@angular/core';
import { ContinutFilmService } from 'src/app/servicii/continut-film.service';
import { ObiectePersistenteModule } from '../obiecte-persistente.module';

@Component({
  selector: 'app-review',
  templateUrl: './review.component.html',
  styleUrls: ['./review.component.scss']
})
export class ReviewComponent implements OnInit {

  constructor(private continut:ContinutFilmService) { }

  ngOnInit(): void {
  }

  @Input() stele:number = 0;
  @Input() nume:string ='';

  review(numar:number){
    this.stele = numar;
    this.continut.adaugaReview(this.nume, this.stele);
  }

  obtineCuloare(numar:number){
    return (this.stele >= numar) ? 'warn' : 'primary';
  }

}
