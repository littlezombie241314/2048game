import Foundation

enum SupportedCountry: String, CaseIterable, Identifiable {
    case china = "CN"
    case unitedStates = "US"

    var id: String { rawValue }

    var displayName: String {
        switch self {
        case .china:
            return "China"
        case .unitedStates:
            return "United States"
        }
    }
}

enum Gender: String, CaseIterable, Identifiable {
    case female
    case male
    case nonBinary
    case preferNotToSay

    var id: String { rawValue }

    var displayName: String {
        switch self {
        case .female: return "Female"
        case .male: return "Male"
        case .nonBinary: return "Non-binary"
        case .preferNotToSay: return "Prefer not to say"
        }
    }
}

struct UserProfile {
    let fullName: String
    let email: String
    let country: SupportedCountry
    let gender: Gender
    let platform: AppPlatform
    var isVerifiedFemale: Bool
}

struct DeliveryOrder: Identifiable {
    let id = UUID()
    let pickupAddress: String
    let dropoffAddress: String
    let packageDescription: String
    let note: String
    let country: SupportedCountry
    let platform: AppPlatform
    let estimatedFeeUSD: Decimal
    let paymentProvider: PaymentProvider
    var isPaid: Bool
}
