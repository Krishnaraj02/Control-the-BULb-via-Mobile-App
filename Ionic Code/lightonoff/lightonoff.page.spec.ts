import { ComponentFixture, TestBed } from '@angular/core/testing';
import { LightonoffPage } from './lightonoff.page';

describe('LightonoffPage', () => {
  let component: LightonoffPage;
  let fixture: ComponentFixture<LightonoffPage>;

  beforeEach(async(() => {
    fixture = TestBed.createComponent(LightonoffPage);
    component = fixture.componentInstance;
    fixture.detectChanges();
  }));

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
