import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class ContinutFilmService {

  constructor() { 
    this.citesteFilme();//google zice ca OnInit nu merge pt servicii asa ca punem asta aici
  }


  citesteFilme(){
    var filmeCitite:any = localStorage.getItem("filme");
    this.filme = JSON.parse(filmeCitite);
  }

  salveazaFilm(nume:string, regizor:string, durata:number, an: number, descriere:string){
    if(this.filme == null)
      this.filme = [];
    var filmNou = {nume:nume, regizor:regizor, durata:durata, an:an, descriere:descriere, stele:0};
    this.filme.push(filmNou);

    localStorage.setItem("filme", JSON.stringify(this.filme));
  }

  adaugaReview(nume:string, stele:number){
    this.filme.forEach((element, index) => {
      if(element.nume == nume){
        this.filme[index].stele = stele;
      }
    });
  }

  salveazaReview(){
    localStorage.setItem("filme", JSON.stringify(this.filme));
    alert("Review-ul a fost salvat cu succes");
  }

  filme:Film[]=[];

  getContinutFilm(): Film[]{
    return this.filme;
  }
}

export interface Film{
  nume: string;
  regizor: string;
  durata: number;
  descriere: string;
  an: number;
  stele: number;
}