데디케이트 서버를 활용한 멈티플레이 구현 및 플러그인 활용

1. 프로젝트 내용
    - 데디케이트 서버 환경을 구축하여 2인 이상의 멀티플레이가 가능한 프로젝트 구현
    - GameMode와 하위 객체를 통해 숫자 야구 로직이 동작하도록 구현
    - 서버에 Login 하는 클라이언트의 순서대로 넘버링하여 유저 이름을 할당
    - 클라이언트 수가 2 이상이고, 접속한 클라이언트가 모두 준비 완료되면 게임 시작
    

2. 게임 룰
    - GameMode에 Component로 생성된 객체가 1 ~ 9 사이의 중복 없는 세 개의 값 선택
    - 10 초 주기로 클라이언트 순서대로 정답 제출 기회 제공
    - 10 초 안에 정답을 입력하지 못 하면 Out
    - 입력한 정답을 Component가 정답과 비교하여 S, B 카운트 출력, 만약 B가 0이라면 Out 처리
    - 다른 플레이어가 Out 되고, 하나의 플레이어만 남는다면 정답 유무와 상관없이 해당 플레이어 승리
    - 유일 생존이 아닌 상태로 정답을 맞추면 해당 플레이어 승리
    - 승리 시, 스코어가 올라가며, 게임이 총 5회 진행되면 게임이 종료되고 클라이언트를 서버에서 내보냄
    - 게임 중, 채팅 가능하며, 입력한 숫자에 대한 결과가 로그로 출력


3. GameMode
    - Title Level에서 각 클라이언트마다 존재하는 싱글플레이 상태로 동작.
    - InGame Level 진입 시, 데디케이트 서버에 진입하며 서버의 Game Mode에 동기화
    - 서버의 Game Mode는 클라이언트의 Login이나 상태를 체크
    - 클라이언트가 Login 하면, 서버에 접속 중인 클라이언트의 수를 체크하여 해당 값을 클라이언트에 할당(일종의 ID)
    - 게임에 필요한 클라이언트가 모두 입장하면 게임 자동 시작
    - 게임의 룰에 따라 동작 수행


5. GameState
    - 서버의 GameMode나 PlayerController에 의해 호출되며, NetMulticast를 수행
    - 접속 중인 클라이언트에게 새로 유저가 접속했음을 채팅창에 출력하도록 클라이언트들의 로컬 GameInstance에 요청
    - 게임 진행 중 유저의 입력을 Log에 출력하도록 클라이언트들의 로컬 GameInstance에 요청
    - 게임의 시작, 결과, 점수를 출력하도록 클라이언트들의 로컬 GameInstance에 요청
    - 유저의 채팅 입력을 채팅 로그에 출력하도록 클라이언트들의 로컬 GameInstnace에 요청
    - 서버는 UI를 출력하지 않으므로, Authority 체크하여 서버에는 요청하지 않도록 구현


6. GameInstance
    - 클라이언트의 동작에 필요한 기능 구현 및 데이터 관리
    - 유저의 이름을 저장 및 반환 (플러그인 구현 및 적용)
    - UISubsystem, LevelSubsystem 이라는 GameInstance Subsystem을 커스텀한 클래스 객체와 상호작용
    - UISubsystem에 Widget Load, Create 및 출력 등의 UI와 관련된 기능을 구현 (Developper Settings를 활용하여 Widget 에셋 로드)
    - LevelSubsystem에 Levvel 이동에 관한 기능 구현


7. PlayerController
    - 서버에 로그인 한 후, 서버의 GameMode로부터 넘버링을 전달받아 User + Number의 형태로 GameInstance에 유저 이름 저장
    - 유저가 채팅을 입력하면 서버에게 요청하여 서버의 GameState로부터 NetMulticast로 채팅 로그를 출력하도록 요청
    - 유저의 입력 내용을 서버에 전달
    - 플레이어의 턴이 되면 정답 입력 창을 출력하도록 로컬 GameInstance에 요청

  
8. Plugin 구현
    - 다른 프로젝트로부터 플레이어의 이름을 입력받거나 반환하는 MyIDPlugin 생성
    - 생성한 플러그인에 필요한 Set, Get 함수와 이름을 저장할 FName 타입의 변수를 static으로 구현
    - 구현한 플러그인 패키징
    - 패키징 된 플러그인을 MultiPlayPrj 프로젝트의 Plugin 폴더에 복사
    - 해당 플러그인이 플러그인 셋팅에 출력되고, 블루프린트에서도 함수로 출력되는 것을 확인
    - Build.cs 파일에 플러그인 모듈 추가
    - 기존의 커스텀한 GameInstance의 SetUserName, GetUserName 함수의 구현부를 MyIDPlugin의 함수로 수정
  
    8.1. 에러 사항 :
   
          - 플러그인으로 생성한 BP Library 클래스에 API를 빼먹어 C++에서 호출할 때 에러가 남
          - PIE 실행 환경을 단일 프로세스로 설정해둔 탓에 같은 값을 공유하는 것처럼 동작
  
10. 실행 화면
   ![image](https://github.com/user-attachments/assets/08bb50cc-aec4-40ef-9641-34a80e451490)

