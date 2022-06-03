import { ComponentFixture, TestBed } from '@angular/core/testing';

import { PaginafilmeComponent } from './paginafilme.component';

describe('PaginafilmeComponent', () => {
  let component: PaginafilmeComponent;
  let fixture: ComponentFixture<PaginafilmeComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ PaginafilmeComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(PaginafilmeComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
