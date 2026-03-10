import Foundation

enum AppPlatform: String, CaseIterable, Identifiable {
    case ios
    case android
    case web

    var id: String { rawValue }

    var displayName: String {
        switch self {
        case .ios: return "iOS"
        case .android: return "Android"
        case .web: return "Web"
        }
    }
}

enum PaymentProvider: String, CaseIterable {
    case applePay = "Apple Pay"
    case stripe = "Stripe"
    case alipay = "Alipay"
    case wechatPay = "WeChat Pay"
    case googlePay = "Google Pay"
}

struct PlatformConfig {
    let platform: AppPlatform
    let enabledCountries: [SupportedCountry]
    let paymentProvidersByCountry: [SupportedCountry: [PaymentProvider]]

    func supports(country: SupportedCountry) -> Bool {
        enabledCountries.contains(country)
    }

    func paymentProviders(for country: SupportedCountry) -> [PaymentProvider] {
        paymentProvidersByCountry[country] ?? []
    }
}

enum PlatformRegistry {
    static let configs: [AppPlatform: PlatformConfig] = [
        .ios: PlatformConfig(
            platform: .ios,
            enabledCountries: [.china, .unitedStates],
            paymentProvidersByCountry: [
                .china: [.alipay, .wechatPay, .applePay],
                .unitedStates: [.stripe, .applePay]
            ]
        ),
        .android: PlatformConfig(
            platform: .android,
            enabledCountries: [.china, .unitedStates],
            paymentProvidersByCountry: [
                .china: [.alipay, .wechatPay],
                .unitedStates: [.stripe, .googlePay]
            ]
        ),
        .web: PlatformConfig(
            platform: .web,
            enabledCountries: [.china, .unitedStates],
            paymentProvidersByCountry: [
                .china: [.alipay, .wechatPay],
                .unitedStates: [.stripe]
            ]
        )
    ]

    static func config(for platform: AppPlatform) -> PlatformConfig {
        configs[platform]!
    }
}
