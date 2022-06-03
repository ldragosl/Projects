import { ComponentFixture, TestBed } from '@angular/core/testing';

import { PaginaContactComponent } from './pagina-contact.component';

describe('PaginaContactComponent', () => {
  let component: PaginaContactComponent;
  let fixture: ComponentFixture<PaginaContactComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ PaginaContactComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(PaginaContactComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
