import { Component, OnInit } from '@angular/core';
import { HttpClient} from '@angular/common/http';


@Component({
  selector: 'app-lightonoff',
  templateUrl: './lightonoff.page.html',
  styleUrls: ['./lightonoff.page.scss'],
})
export class LightonoffPage implements OnInit {
  lightStatus: string = '';
  onOff: boolean = false;

  constructor(private http: HttpClient) {}

  ngOnInit() {}



  lightoff() {
    this.http.get('http://localhost:9111/off').subscribe(
      () => {
        this.lightStatus = 'Stop';
      },
      (error) => {
        console.error('Failed to turn off the light:', error);
      }
    );
  }

  lighton() {
    
    this.http.get('http://localhost:9111/on').subscribe(
      () => {
        this.lightStatus = 'Start';
      },
      (error) => {
        console.error('Failed to turn on the light:', error);
      }
    );
  }
}
