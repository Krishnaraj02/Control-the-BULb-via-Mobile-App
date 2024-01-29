import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

import { IonicModule } from '@ionic/angular';

import { LightonoffPageRoutingModule } from './lightonoff-routing.module';

import { LightonoffPage } from './lightonoff.page';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    LightonoffPageRoutingModule
  ],
  declarations: [LightonoffPage]
})
export class LightonoffPageModule {}
