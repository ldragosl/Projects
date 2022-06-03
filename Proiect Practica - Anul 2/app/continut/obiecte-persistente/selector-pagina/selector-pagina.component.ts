import { Component, Input, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { ObiectePersistenteModule } from '../obiecte-persistente.module';

@Component({
  selector: 'app-selector-pagina',
  templateUrl: './selector-pagina.component.html',
  styleUrls: ['./selector-pagina.component.scss']
})
export class SelectorPaginaComponent implements OnInit {

  @Input() index!: number;

  constructor(private router:Router) { }

  ngOnInit(): void {

  }
  home(){
    this.router.navigate(['']);
  }
  filme(){
    this.router.navigate(['filme']);
  }
  contact(){
    this.router.navigate(['contact']);
  }
  legal(){
    this.router.navigate(['legal']);
  }

  obtineCuloareHome(){
    return this.index == 1 ? "accent" : "primary";
  }
  obtineCuloareFilme(){
    return this.index == 2 ? "accent" : "primary";
  }
  obtineCuloareAbout(){
    return this.index == 4 ? "accent" : "primary";
  }
  obtineCuloareContact(){
    return this.index == 3 ? "accent" : "primary";
  }

}
