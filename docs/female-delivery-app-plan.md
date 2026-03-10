# 女生送货 / Female Delivery（iOS）产品开发方案（V1）

## 1. 项目目标
- **中文名**：女生送货
- **英文名**：Female Delivery
- **平台**：iOS（首发 App Store）
- **服务国家**：长期目标全球
- **首批上线国家**：中国、美国
- **配送类型**：送货（即时同城配送）
- **用户限制**：仅允许女性注册与下单
- **骑手限制**：仅允许女性接单与配送
- **支付方式**：在线支付

---

## 2. 角色与权限

### 2.1 C 端用户（女性）
核心能力：
1. 女性身份注册与认证
2. 下单（取件地、收件地、物品类型、备注、时间）
3. 价格预估与在线支付
4. 实时查看配送状态与地图轨迹
5. 联系骑手（匿名号/应用内聊天）
6. 订单评价与售后申请

### 2.2 骑手端（女性）
核心能力：
1. 女性身份认证与审核
2. 接单、到店/到点取件、配送签收
3. 导航与路径优化
4. 收入统计、提现
5. 风险上报（一键报警、异常订单上报）

### 2.3 平台运营后台
核心能力：
1. 用户/骑手审核
2. 订单与风控监控
3. 国家与城市开通管理
4. 费率、补贴、活动配置
5. 客服工单处理

---

## 3. 核心业务流程（MVP）
1. 用户注册 -> 女性认证通过
2. 用户创建送货订单 -> 价格计算
3. 用户在线支付（预授权或实付）
4. 系统派单/骑手抢单
5. 骑手取件 -> 配送中 -> 签收
6. 订单完成 -> 结算分账 -> 评价
7. 异常场景：取消、超时、物品违规、退款

---

## 4. 功能范围（首发版本）

### 4.1 必做功能
- 手机号/邮箱注册登录（支持中国、美国）
- 女性身份审核（证件 + 人脸核验 + 人工复审）
- 地址管理（中美地址格式兼容）
- 下单与智能计价（距离、时段、天气、重量）
- 在线支付
  - 中国：微信支付、支付宝、Apple Pay（可选）
  - 美国：Stripe（银行卡）、Apple Pay
- 订单状态流转与消息通知（推送 + 站内）
- 实时定位与轨迹
- 评价体系与客服入口

### 4.2 可选增强
- 预约单
- 多件合并配送
- 夜间安全模式（分享行程、紧急联系人）
- 女性专属隐私保护（虚拟号码、地址脱敏）

---

## 5. 技术架构建议

### 5.1 客户端
- **iOS 原生**：Swift + SwiftUI（推荐）
- 地图：
  - 中国：高德地图/腾讯地图
  - 美国：Google Maps / Apple MapKit
- 推送：APNs

### 5.2 服务端
- API：RESTful + JWT/OAuth2
- 核心服务：
  - 用户与认证服务
  - 订单服务
  - 派单服务
  - 支付与结算服务
  - 风控与审核服务
  - 消息服务
- 数据层：PostgreSQL + Redis
- 对象存储：S3/OSS（证件与订单凭证）
- 监控：Prometheus + Grafana + Sentry

### 5.3 合规与安全
- 数据加密：传输 TLS 1.2+，敏感字段静态加密
- 最小权限访问与审计日志
- 地区化数据存储策略（CN/US 分区）
- 隐私条款、用户协议、退款规则

---

## 6. “仅女性可用”实施方案（关键）

> 说明：该策略可能涉及不同国家/地区反歧视法规与平台审核风险，必须由法务审查后落地。

实施建议：
1. 注册阶段要求提交法定身份证明与人脸核验
2. 审核通过后开放下单/接单权限
3. 定期复核 + 异常行为二次验证
4. 在隐私政策中明确采集目的、保存周期、删除机制
5. 提供人工申诉通道，降低误伤

---

## 7. App Store 上架关键清单
1. Apple 开发者账号（公司主体）
2. App 隐私清单（定位、支付、身份信息采集说明）
3. 内容审核材料：
   - 业务模式说明
   - 女性认证流程说明
   - 用户与骑手安全机制
4. IAP 判定：平台撮合型服务通常可走第三方支付（需再次核对 Apple 最新规则）
5. 审核测试账号（中国/美国环境）
6. 多语言文案：中文（简体）、英文（美国）

---

## 8. 建议里程碑（12 周 MVP）
- **第 1-2 周**：需求冻结、原型图、技术选型
- **第 3-6 周**：iOS 用户端 + 后端核心 API
- **第 7-8 周**：骑手端核心流程 + 支付联调
- **第 9-10 周**：风控审核、监控告警、性能压测
- **第 11 周**：TestFlight 内测（中国/美国）
- **第 12 周**：修复问题并提交 App Store

---

## 9. 首发城市建议（中美）
- 中国：上海、深圳（高密度即时配送场景）
- 美国：Los Angeles、New York（高需求与支付成熟）

---

## 10. 下一步可直接执行
1. 我可以继续为你输出：
   - iOS 信息架构图（页面树）
   - 数据库表结构（用户/骑手/订单/支付）
   - OpenAPI 接口文档（可直接给开发）
2. 你确认后，我们先做 **MVP 功能清单 + 原型图 + 技术任务拆分（按周）**。


## 11. 多平台上架代码改造建议（iOS / Android / Web）
1. 平台能力配置中心：将国家开通、支付方式、功能开关抽象为 `PlatformConfig`（当前代码已示例）。
2. 统一业务模型：订单、支付、实名认证字段保持跨端一致，避免平台分叉。
3. 支付网关层：客户端仅选择支付方式，具体路由由后端按国家与平台决策。
4. Feature Flag：将平台与国家放量逻辑放到服务端，支持灰度发布。
5. 多端 UI 复用策略：
   - iOS：SwiftUI
   - Android：Kotlin + Compose（对齐同一 API）
   - Web：React/Vue（同一 API）
6. 上架流程拆分：每个平台单独产物与审核素材，但共用产品规则与后端。


## 12. 直接多平台上架实现路径（已落地代码）
- 新增 `FemaleDeliveryCrossPlatform/` Flutter 单代码库，可直接产出 iOS/Android/Web。
- 统一实现了女性准入、国家开通、支付通道映射、送货下单与支付流程。
- 上架时建议：
  1. iOS 使用 `flutter build ios` 后走 Xcode 提交 App Store；
  2. Android 使用 `flutter build appbundle` 后提交 Google Play；
  3. Web 使用 `flutter build web` 后部署到全球 CDN。

## 13. 多平台上架详细步骤（中英逐行）
### 13.1 iOS（App Store）
1. 中文：在 Apple Developer 创建 App ID、Bundle ID，并在 Xcode 配置签名证书与 Provisioning Profile。
   English: Create the App ID and Bundle ID in Apple Developer, then configure signing certificates and provisioning profiles in Xcode.
2. 中文：在 App Store Connect 新建应用，填写应用名称（女生送货 / Female Delivery）、隐私政策链接、分级与类目。
   English: Create a new app in App Store Connect and fill in app name (女生送货 / Female Delivery), privacy policy URL, age rating, and category.
3. 中文：执行 `flutter build ios`（或原生 iOS 工程 Archive），在 Xcode Organizer 上传构建包。
   English: Run `flutter build ios` (or archive the native iOS project) and upload the build via Xcode Organizer.
4. 中文：在 App Store Connect 绑定版本、上传截图（iPhone 尺寸）、填写审核备注和测试账号。
   English: Attach the build to a version in App Store Connect, upload screenshots (iPhone sizes), and provide review notes plus test accounts.
5. 中文：提交审核并跟进驳回问题，审核通过后按国家/地区发布（首发中国、美国）。
   English: Submit for review and address any rejection feedback, then release by country/region (first launch: China and the US).

### 13.2 Android（Google Play）
1. 中文：在 Google Play Console 创建应用，配置应用包名、应用签名（Play App Signing）和开发者信息。
   English: Create the app in Google Play Console and configure package name, Play App Signing, and developer profile.
2. 中文：执行 `flutter build appbundle` 生成 AAB，并上传到内部测试或封闭测试轨道。
   English: Run `flutter build appbundle` to generate an AAB, then upload it to internal or closed testing tracks.
3. 中文：填写商店信息（多语言标题、描述、功能亮点）、隐私政策链接、内容分级与数据安全表单。
   English: Complete store listing details (localized title, description, highlights), privacy policy URL, content rating, and data safety form.
4. 中文：配置目标国家与定价策略，首批发布国家设置为中国和美国。
   English: Configure target countries and pricing strategy, with first-wave release set to China and the US.
5. 中文：通过预发布报告与政策合规检查后，提交生产发布并逐步放量。
   English: After passing pre-launch reports and policy checks, submit to production and roll out gradually.

### 13.3 Web（全球部署）
1. 中文：执行 `flutter build web` 生成静态站点构建产物。
   English: Run `flutter build web` to generate static web build artifacts.
2. 中文：将构建产物部署到 CDN/对象存储（如 CloudFront+S3、Cloudflare Pages、Vercel 或阿里云 OSS）。
   English: Deploy build artifacts to CDN/object storage (e.g., CloudFront+S3, Cloudflare Pages, Vercel, or Alibaba Cloud OSS).
3. 中文：配置 HTTPS 证书、域名、跨域策略（CORS）与缓存策略。
   English: Configure HTTPS certificates, custom domains, CORS policy, and cache strategy.
4. 中文：接入 Web 支付通道（如 Stripe Checkout），并按国家展示可用支付方式。
   English: Integrate web payment providers (e.g., Stripe Checkout) and display available payment methods by country.
5. 中文：上线后开启监控（前端错误、性能、支付成功率）并进行灰度发布与回滚预案。
   English: After launch, enable monitoring (frontend errors, performance, payment success rate) and apply canary rollout plus rollback plans.

### 13.4 共通合规步骤（所有平台）
1. 中文：完成女性准入机制的法务审查，明确适用国家法律与用户申诉流程。
   English: Complete legal review of the women-only access policy, including country-specific law applicability and appeal workflows.
2. 中文：完善《用户协议》《隐私政策》《退款规则》，并在应用内可访问。
   English: Finalize Terms of Service, Privacy Policy, and Refund Policy, and make them accessible in-app.
3. 中文：完成账号注销、数据导出、数据删除流程，满足隐私合规要求。
   English: Implement account deletion, data export, and data erasure flows to meet privacy compliance requirements.
4. 中文：建立风控与客服 SOP（异常订单、支付争议、身份误判复核）。
   English: Establish risk-control and customer-support SOPs (abnormal orders, payment disputes, and identity review appeals).
5. 中文：准备多语言客服与运营素材，确保中国和美国首发体验一致。
   English: Prepare multilingual support and operational assets to ensure a consistent first-launch experience in China and the US.

## 14. 女生风格 UI 与 Windows 交互改造（已落地）
- 中文：界面配色已改为柔和粉色系，强化圆角卡片、轻渐变头图、爱心与安全感视觉元素。
  English: The UI palette has been updated to a soft pink style with rounded cards, gentle gradient headers, and trust-oriented visual cues.
- 中文：移动端保持简洁表单流，突出下单与支付主路径。
  English: Mobile keeps a simple form-first flow with emphasis on ordering and payment actions.
- 中文：Windows 端增加桌面友好交互，包括悬停动效、卡片放大反馈、双栏布局与更大点击区域。
  English: Windows introduces desktop-friendly interactions, including hover animations, card scale feedback, two-column layout, and larger click targets.
