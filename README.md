# ramen-kiosk
22-2 객체지향프로그래밍 팀프로젝트 3조
<br/>
라면 주문 및 결제 키오스크를 제작합니다. 

# 작업 컨벤션
### Issue 생성
> 작업할 내용으로 이슈를 생성합니다.
- 이슈제목
```
[FEAT] 메뉴 아이템 구현
[CHORE] 메뉴 아이템에서 불필요한 코드 삭제
```

- 이슈내용
```
## 🎧 이슈 요약
<!-- 해당 이슈에서 할 작업에 대해 설명해주세요. -->

## 🎹 체크 리스트
<!-- 해야 할 일을 적어주세요. -->
- [ ] todo
```

### Branch 생성
> `분류` /`#이슈 번호` - `작업할 부분`
- 가장 처음에 붙는 분류 영역에서는, 커밋 컨벤션의 워딩과 동일하게 작성합니다.
```
chore/#3-Cart
feat/#3-Menu
fix/
```

### Commit 생성
> 작업 내용에 따라 커밋 메시지를 달리합니다.
- 커밋 메시지
```
[CHORE] 그냥 보통 작업 있잖아요.. 잡일 #2
[FEAT] 새로운 주요 기능 추가 #2
[ADD] 파일 추가, 에셋 추가, etc... #2
[FIX] 버그 수정 #2
[DEL] 쓸모없는 코드, 뭐 어쩌고 삭제 #2
[MOVE] 프로젝트 구조 변경(폴더링 등) #2
[RENAME] 파일, 클래스, 변수명 등 이름 변경 #2
[DOCS] Wiki, README 파일 수정 #2
```

### PR 생성
> 작업 완료 후 pull request를 날립니다. 
- PR 제목
```
[FEAT] 메뉴 아이템 구현 
[CHORE] 메뉴 아이템에서 불필요한 코드 삭제
```

- PR 내용
```
## 작업한 내용
- 작업 내용 1

## PR Point
<!-- 피드백을 받고 싶은 부분, 공유하고 싶은 부분, 작업 과정, 이유를 적어주세요. -->
- PR Point 1
- PR Point 2

## 스크린샷
<!-- gif or mp4 용량 제한이 있는데... 용량 넘어가면 슬랙으로 보내 주세요. -->


## 관련 이슈
- Resolved: #이슈번호

<!-- 아 맞다! Assignee, Reviewer 설정! 😇 -->
```

### Merge
> `PR`은 모두의 확인을 받아야 `Merge`가 가능합니다.
> 모든 작업이 완료되어 `Merge`가 된 경우, 해당 `PR` 하단의 `Delete Branch`를 선택하여 작업이 끝난 `Branch`를 삭제합니다.
