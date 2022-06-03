import { ComponentFixture, TestBed } from '@angular/core/testing';

import { SelectorPaginaComponent } from './selector-pagina.component';

describe('SelectorPaginaComponent', () => {
  let component: SelectorPaginaComponent;
  let fixture: ComponentFixture<SelectorPaginaComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ SelectorPaginaComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(SelectorPaginaComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
