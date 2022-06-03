import { analyzeAndValidateNgModules } from '@angular/compiler';
import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { ServiciuLogareService } from './servicii/serviciu-logare.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent implements OnInit {
  title = 'ProiectAngular';
  constructor( private router:Router, private serviciuLogare:ServiciuLogareService){

  }

  ngOnInit(): void {
    this.serviciuLogare.loginAutomat();
  }
}