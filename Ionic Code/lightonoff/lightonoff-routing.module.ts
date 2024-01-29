import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { LightonoffPage } from './lightonoff.page';

const routes: Routes = [
  {
    path: '',
    component: LightonoffPage
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule],
})
export class LightonoffPageRoutingModule {}
