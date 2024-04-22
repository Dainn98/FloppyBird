# ***Floppy Bird*** 

## **Introduction** 

+ Họ và tên: Phạm Tuấn Anh - K68CB - UET

+ Mã sinh viên: 23020010 

+ Bài tập lớn: Floppy Bird (INT2215_50 - Lập trình nâng cao) 

## **Description** 
### *Game description and instruction* 
- Đây là trò chơi được phát triển theo một hướng hoàn toàn khác với nhiều tính năng hay, vượt trội so với trò chơi Flappy Bird.
Bứt phá khỏi lối chơi truyền thống, Floppy Bird mang đến những tính năng độc đáo và đầy hấp dẫn:
- Gameplay:
  + Thay vì chỉ tập trung vào việc điều khiển chim bay qua các chướng ngại vật, người chơi có thể sử dụng thêm tính năng bắn đạn để tiêu diệt chúng.
  + Việc kiếm tiền thưởng bằng cách ăn vàng và tiêu diệt chướng ngại vật tạo thêm động lực cho người chơi tiếp tục chơi.
  +  Có thêm các chướng ngại vật bất ngờ như cây ăn thịt và tảng băng rơi mang đến yếu tố thử thách và bất ngờ, khiến trò chơi trở nên gay cấn hơn.
  + Bên cạnh các chướng ngại vật, vật phẩm giúp người chơi chống lại các chướng ngại vật, tạo thêm lợi thế và tăng cơ hội tồn tại lâu hơn.
- Có âm thanh sôi động khi chơi game.
- Game có đầy đủ chức năng hỗ trợ người chơi trong việc điều chỉnh giữa các lựa chọn dừng game, chơi lại game, thoát game, mô tả cách chơi, sử dụng phím esc để dừng game,...
- Floppy Bird chắc chắn sẽ không khiến cho người chơi phải thất vọng với những tính năng, đồ họa độc đáo mới lạ.
- Video demo :
### *Control* 

| Control  |   Player   |
|----------|------------|
| UP       |      ↑     |
| DOWN     |      ↓     |
| SHOOTING | BUTTONLEFT |
### *Window Preview*
![](FloppyBird/res/demoImage/IntroDemo.png)
![](FloppyBird/res/demoImage/TapDemo.png)
![](FloppyBird/res/demoImage/TutorialDemo.png)
![](FloppyBird/res/demoImage/endDemo.png)

## **Setup**
//To do
## **See also**  
### *Các kỹ thuật sử dụng*  
- Thư viện SDL2.0
- Sử dụng nhiều class, vector, tách file, con trỏ, xâu chuỗi,biến, vòng lặp, cấu trúc rẽ nhánh, mảng, ...
- Tạo nhiều đối tượng với từng class riêng: tiền, chướng ngại vật, đạn bắn, chim, vật phẩm, ...
- Có thể lưu lại điểm cao nhất sau mỗi lần chơi nhờ đọc và ghi file.
- Xử lý thời gian, thao tác chuột và bàn phím, âm thanh, hình ảnh, chữ.
- Tạo menu và các nút ấn di chuyển giữa các menu.
- Tạo Option khi chơi : pause game, play game, restart game, exit game.
- Sử dụng photoshop để edit các ảnh dựa vào một số mẫu ảnh từ các nguồn khác.
- Có sử dụng kiến thức toán học để tính toán va chạm của các đối tượng.

### *Các nguồn tham khảo*
- Cách sử dụng, cài đặt SDL2.0 trên C++: tham khảo từ các bạn, kênh youtube TOAN - TIN IUH.
- Cách sử dụng, thư viện SDL2.0, quản lý chương trình:
    + Tham khảo trên LazyFool.
    + Các buổi lý thuyết của TS.Lê Đức Trọng.
    + Các buổi thực hành của CN. Trần Trường Thủy.
    + Kênh youtube: Let's Make Games, PolyMars, Madsycode.
- Hình ảnh: các nguồn trên google, pinterest,..
    + https://www.spriters-resource.com/mobile/flappybird/sheet/59894/
- Âm thanh: các nguồn trên google
  
    + https://pixabay.com/sound-effects/search/wav/
    #Free Wav Sound Effects Download
    + https://www.freesoundeffects.com/free-sounds/explosion-10070/
    #Free Explosion Sound Effects
 ...
## **Conclusion**
### ***Điều tâm đắc***
  - Dự án này hoàn toàn là do em tự làm, không đi sao chép ở bất kì đâu.
  - Hiểu được mô hình phát triển 1 phần mềm kiểu thác nước: Phân tích, thiết kế, lập trình, kiểm thử, vận hành và bảo trì.
  - Cách dùng github.
  - Hiểu sơ sơ một số khía cạnh của lập trình hướng đối tượng: kế thừa, đa hình,...
  - Sau khi làm dự án này, em thấy mình đã cải thiện được nhiều kỹ năng trong việc tư duy và viết code, khả năng lên ý tưởng, sắp xếp chia tách file và các kỹ năng photoshop.
  - Học được cách setup môi trường, sử dụng thư viện ngoài (SDL2, SDL2_ttf, SDL2_mixer, SDL2_image, ...)
  - Cải thiện kỹ năng sử dụng class (constructor, destructor, member function,...).  
  - Học được kỹ thuật refactor code, duyệt mảng, sinh số ngẫu nhiên, giải phóng bộ nhớ động.
  - Cải thiện kỹ năng tối ưu hóa code bằng việc destructor các đối tượng trong mỗi class, khởi tạo và giải phóng bộ nhớ động, ...
    
### ***Hạn chế*** 
  - Một số đối tượng trong chương trình vẫn đang được quản lý theo vector kiểu con trỏ nên việc phải tự xóa sau khi không sử dụng là việc không dễ dàng
  - Một số phần code chưa trong sáng.

### ***Hướng phát triển***
- Cập nhật tính năng bảng xếp hạng, sau mỗi lần chơi người chơi sẽ được nhập tên để lưu lại kết quả chơi của mình
- Thêm nhiều loại vật phẩm có tính năng khác nhau: phóng to, thu nhỏ, tên lửa,...
- Thêm các chế độ điều chỉnh tốc độ để người chơi để có thể chọn tốc độ tùy thích, phù hợp với khả năng chơi của mình.
- Thêm các chế độ 2 Player, VS Computer, ... để người chơi cạnh tranh với nhau.
- Áp dụng hệ thống sử dụng tiền và nạp tiền:
    + Thêm cửa hàng để mua trang phục và vật phẩm bổ trợ.
    + Sử dụng tiền thưởng kiếm được từ việc nạp tiền hoặc đạt được lúc chơi game.
    + Người chơi nạp tiền vào game, số tiền sẽ chuyển vào tài khoản nhà phát hành.
- Sử dụng kết nối mạng máy tính (LAN, Router,...) kết nối người chơi cạnh tranh với nhau.
  
### ***A Special Thanks:***
- TS. Lê Đức Trọng - Người hướng dẫn, Giảng viên.
- CN. Trần Trường Thủy - Người hướng dẫn, Giảng viên.
- SV Nguyễn Hoàng Dương - Cố vấn.

### *Mức điểm tự đánh giá: **/10* 
