import 'dart:math';

import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';

enum SupportedCountry { china, us }

enum Gender { female, male, nonBinary, undisclosed }

enum AppPlatform { ios, android, web, windows }

enum PaymentProvider { applePay, googlePay, stripe, alipay, wechatPay }

extension Display on SupportedCountry {
  String get label => this == SupportedCountry.china ? 'China' : 'United States';
}

extension PlatformDisplay on AppPlatform {
  String get label {
    switch (this) {
      case AppPlatform.ios:
        return 'iOS';
      case AppPlatform.android:
        return 'Android';
      case AppPlatform.web:
        return 'Web';
      case AppPlatform.windows:
        return 'Windows';
    }
  }
}

extension GenderDisplay on Gender {
  String get label {
    switch (this) {
      case Gender.female:
        return 'Female';
      case Gender.male:
        return 'Male';
      case Gender.nonBinary:
        return 'Non-binary';
      case Gender.undisclosed:
        return 'Prefer not to say';
    }
  }
}

extension PaymentDisplay on PaymentProvider {
  String get label {
    switch (this) {
      case PaymentProvider.applePay:
        return 'Apple Pay';
      case PaymentProvider.googlePay:
        return 'Google Pay';
      case PaymentProvider.stripe:
        return 'Stripe';
      case PaymentProvider.alipay:
        return 'Alipay';
      case PaymentProvider.wechatPay:
        return 'WeChat Pay';
    }
  }
}

class PlatformConfig {
  const PlatformConfig({
    required this.platform,
    required this.enabledCountries,
    required this.providers,
  });

  final AppPlatform platform;
  final List<SupportedCountry> enabledCountries;
  final Map<SupportedCountry, List<PaymentProvider>> providers;

  bool supportsCountry(SupportedCountry country) => enabledCountries.contains(country);

  List<PaymentProvider> paymentProviders(SupportedCountry country) => providers[country] ?? const [];
}

class PlatformRegistry {
  static const Map<AppPlatform, PlatformConfig> configs = {
    AppPlatform.ios: PlatformConfig(
      platform: AppPlatform.ios,
      enabledCountries: [SupportedCountry.china, SupportedCountry.us],
      providers: {
        SupportedCountry.china: [PaymentProvider.alipay, PaymentProvider.wechatPay, PaymentProvider.applePay],
        SupportedCountry.us: [PaymentProvider.stripe, PaymentProvider.applePay],
      },
    ),
    AppPlatform.android: PlatformConfig(
      platform: AppPlatform.android,
      enabledCountries: [SupportedCountry.china, SupportedCountry.us],
      providers: {
        SupportedCountry.china: [PaymentProvider.alipay, PaymentProvider.wechatPay],
        SupportedCountry.us: [PaymentProvider.stripe, PaymentProvider.googlePay],
      },
    ),
    AppPlatform.web: PlatformConfig(
      platform: AppPlatform.web,
      enabledCountries: [SupportedCountry.china, SupportedCountry.us],
      providers: {
        SupportedCountry.china: [PaymentProvider.alipay, PaymentProvider.wechatPay],
        SupportedCountry.us: [PaymentProvider.stripe],
      },
    ),
    AppPlatform.windows: PlatformConfig(
      platform: AppPlatform.windows,
      enabledCountries: [SupportedCountry.china, SupportedCountry.us],
      providers: {
        SupportedCountry.china: [PaymentProvider.alipay, PaymentProvider.wechatPay],
        SupportedCountry.us: [PaymentProvider.stripe],
      },
    ),
  };

  static PlatformConfig of(AppPlatform platform) => configs[platform]!;
}

class UserProfile {
  UserProfile({
    required this.fullName,
    required this.email,
    required this.gender,
    required this.country,
    required this.platform,
    required this.verifiedFemale,
  });

  final String fullName;
  final String email;
  final Gender gender;
  final SupportedCountry country;
  final AppPlatform platform;
  final bool verifiedFemale;
}

class DeliveryOrder {
  DeliveryOrder({
    required this.pickup,
    required this.dropoff,
    required this.item,
    required this.distanceKm,
    required this.fee,
    required this.provider,
    this.paid = false,
  });

  final String pickup;
  final String dropoff;
  final String item;
  final double distanceKm;
  final double fee;
  final PaymentProvider provider;
  bool paid;
}

String? validateAccess({
  required Gender gender,
  required SupportedCountry country,
  required AppPlatform platform,
}) {
  if (gender != Gender.female) return 'Only female users are allowed.';
  if (!PlatformRegistry.of(platform).supportsCountry(country)) {
    return 'Service is unavailable in ${country.label} for ${platform.label}.';
  }
  return null;
}

double estimateFee(SupportedCountry country, double distanceKm) {
  final base = country == SupportedCountry.china ? 3.5 : 6.0;
  return base + (distanceKm * 0.8);
}

Future<String> mockPay(PaymentProvider provider, String cardLast4) async {
  await Future<void>.delayed(const Duration(milliseconds: 700));
  if (cardLast4.length != 4) throw Exception('Invalid card digits.');
  final random = Random().nextInt(900000) + 100000;
  return '${provider.label.toUpperCase()}-$random';
}

bool get isWindowsDesktop {
  if (kIsWeb) return false;
  return defaultTargetPlatform == TargetPlatform.windows;
}

void main() {
  runApp(const FemaleDeliveryApp());
}

class FemaleDeliveryApp extends StatelessWidget {
  const FemaleDeliveryApp({super.key});

  @override
  Widget build(BuildContext context) {
    final scheme = ColorScheme.fromSeed(
      seedColor: const Color(0xFFE44AA6),
      brightness: Brightness.light,
    ).copyWith(
      primary: const Color(0xFFD93D96),
      secondary: const Color(0xFFFF8AB8),
      tertiary: const Color(0xFFFFC3D9),
      surface: const Color(0xFFFFF5FA),
    );

    return MaterialApp(
      title: 'Female Delivery',
      theme: ThemeData(
        useMaterial3: true,
        colorScheme: scheme,
        scaffoldBackgroundColor: const Color(0xFFFFF0F7),
        cardTheme: const CardThemeData(
          elevation: 0,
          color: Colors.white,
          margin: EdgeInsets.symmetric(vertical: 6),
          shape: RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(18))),
        ),
        inputDecorationTheme: InputDecorationTheme(
          filled: true,
          fillColor: Colors.white,
          border: OutlineInputBorder(borderRadius: BorderRadius.circular(16), borderSide: BorderSide.none),
          contentPadding: const EdgeInsets.symmetric(horizontal: 14, vertical: 12),
        ),
        elevatedButtonTheme: ElevatedButtonThemeData(
          style: ElevatedButton.styleFrom(
            minimumSize: const Size.fromHeight(48),
            shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(14)),
          ),
        ),
      ),
      home: const RegistrationPage(),
    );
  }
}

class PinkHeader extends StatelessWidget {
  const PinkHeader({super.key, required this.title, required this.subtitle});

  final String title;
  final String subtitle;

  @override
  Widget build(BuildContext context) {
    return Container(
      width: double.infinity,
      padding: const EdgeInsets.all(16),
      decoration: BoxDecoration(
        borderRadius: BorderRadius.circular(20),
        gradient: const LinearGradient(
          colors: [Color(0xFFFFC1DA), Color(0xFFFF9BC7), Color(0xFFFF7AB8)],
          begin: Alignment.topLeft,
          end: Alignment.bottomRight,
        ),
      ),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Text(title, style: const TextStyle(color: Colors.white, fontSize: 22, fontWeight: FontWeight.w700)),
          const SizedBox(height: 6),
          Text(subtitle, style: const TextStyle(color: Colors.white, fontSize: 13)),
        ],
      ),
    );
  }
}

class RegistrationPage extends StatefulWidget {
  const RegistrationPage({super.key});

  @override
  State<RegistrationPage> createState() => _RegistrationPageState();
}

class _RegistrationPageState extends State<RegistrationPage> {
  final nameCtrl = TextEditingController();
  final emailCtrl = TextEditingController();
  AppPlatform platform = AppPlatform.ios;
  SupportedCountry country = SupportedCountry.china;
  Gender gender = Gender.female;
  String? error;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('女生送货 / Female Delivery')),
      body: ListView(
        padding: const EdgeInsets.all(16),
        children: [
          const PinkHeader(
            title: '女生友好风格 / Girl-Friendly Theme',
            subtitle: 'Soft pink palette · Rounded cards · Easy interactions',
          ),
          const SizedBox(height: 14),
          DropdownButtonFormField<AppPlatform>(
            value: platform,
            decoration: const InputDecoration(labelText: 'Platform'),
            items: AppPlatform.values
                .map((p) => DropdownMenuItem(value: p, child: Text(p.label)))
                .toList(),
            onChanged: (v) => setState(() => platform = v ?? AppPlatform.ios),
          ),
          const SizedBox(height: 12),
          TextField(controller: nameCtrl, decoration: const InputDecoration(labelText: 'Full Name')),
          const SizedBox(height: 12),
          TextField(controller: emailCtrl, decoration: const InputDecoration(labelText: 'Email')),
          const SizedBox(height: 12),
          DropdownButtonFormField<SupportedCountry>(
            value: country,
            decoration: const InputDecoration(labelText: 'Country'),
            items: SupportedCountry.values
                .map((c) => DropdownMenuItem(value: c, child: Text(c.label)))
                .toList(),
            onChanged: (v) => setState(() => country = v ?? SupportedCountry.china),
          ),
          const SizedBox(height: 12),
          DropdownButtonFormField<Gender>(
            value: gender,
            decoration: const InputDecoration(labelText: 'Gender'),
            items: Gender.values
                .map((g) => DropdownMenuItem(value: g, child: Text(g.label)))
                .toList(),
            onChanged: (v) => setState(() => gender = v ?? Gender.female),
          ),
          if (error != null) ...[
            const SizedBox(height: 12),
            Text(error!, style: TextStyle(color: Theme.of(context).colorScheme.error)),
          ],
          const SizedBox(height: 16),
          ElevatedButton.icon(
            onPressed: () {
              final result = validateAccess(gender: gender, country: country, platform: platform);
              if (result != null) {
                setState(() => error = result);
                return;
              }
              final user = UserProfile(
                fullName: nameCtrl.text.trim(),
                email: emailCtrl.text.trim(),
                gender: gender,
                country: country,
                platform: platform,
                verifiedFemale: true,
              );
              Navigator.of(context).push(MaterialPageRoute(builder: (_) => HomePage(user: user)));
            },
            icon: const Icon(Icons.favorite),
            label: const Text('Create account'),
          ),
        ],
      ),
    );
  }
}

class HomePage extends StatefulWidget {
  const HomePage({super.key, required this.user});

  final UserProfile user;

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  final List<DeliveryOrder> orders = [];

  @override
  Widget build(BuildContext context) {
    final desktop = isWindowsDesktop;
    return Scaffold(
      appBar: AppBar(title: const Text('Female Delivery')),
      floatingActionButton: FloatingActionButton.extended(
        onPressed: () async {
          final order = await Navigator.of(context).push<DeliveryOrder>(
            MaterialPageRoute(builder: (_) => CreateOrderPage(user: widget.user)),
          );
          if (order != null) setState(() => orders.insert(0, order));
        },
        icon: const Icon(Icons.local_shipping),
        label: const Text('New Delivery Order'),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16),
        child: desktop
            ? Row(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Expanded(flex: 2, child: _profilePanel(context)),
                  const SizedBox(width: 16),
                  Expanded(flex: 3, child: _ordersPanel()),
                ],
              )
            : Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  _profilePanel(context),
                  const SizedBox(height: 10),
                  Expanded(child: _ordersPanel()),
                ],
              ),
      ),
    );
  }

  Widget _profilePanel(BuildContext context) {
    return Card(
      child: Padding(
        padding: const EdgeInsets.all(14),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Text('Welcome, ${widget.user.fullName}', style: Theme.of(context).textTheme.titleMedium),
            const SizedBox(height: 4),
            Text('Platform: ${widget.user.platform.label}'),
            Text('Country: ${widget.user.country.label}'),
            const SizedBox(height: 4),
            const Text('Identity: Female verified ✓', style: TextStyle(fontWeight: FontWeight.w600)),
          ],
        ),
      ),
    );
  }

  Widget _ordersPanel() {
    if (orders.isEmpty) {
      return const Center(child: Text('No orders yet. Create your first delivery order.'));
    }

    return ListView.builder(
      itemCount: orders.length,
      itemBuilder: (context, index) {
        final o = orders[index];
        return HoverOrderCard(order: o);
      },
    );
  }
}

class HoverOrderCard extends StatefulWidget {
  const HoverOrderCard({super.key, required this.order});

  final DeliveryOrder order;

  @override
  State<HoverOrderCard> createState() => _HoverOrderCardState();
}

class _HoverOrderCardState extends State<HoverOrderCard> {
  bool hovered = false;

  @override
  Widget build(BuildContext context) {
    final enableHover = isWindowsDesktop || kIsWeb;
    return MouseRegion(
      onEnter: (_) => setState(() => hovered = true),
      onExit: (_) => setState(() => hovered = false),
      child: AnimatedContainer(
        duration: const Duration(milliseconds: 140),
        transform: Matrix4.identity()..scale(enableHover && hovered ? 1.01 : 1.0),
        child: Card(
          shadowColor: hovered ? const Color(0x55FF6AAE) : Colors.transparent,
          elevation: hovered ? 8 : 0,
          child: ListTile(
            contentPadding: const EdgeInsets.symmetric(horizontal: 14, vertical: 8),
            title: Text('${widget.order.pickup} → ${widget.order.dropoff}'),
            subtitle: Text(
              '${widget.order.item} | ${widget.order.provider.label} | \$${widget.order.fee.toStringAsFixed(2)}',
            ),
            trailing: Chip(
              label: Text(widget.order.paid ? 'Paid' : 'Unpaid'),
              backgroundColor: widget.order.paid ? const Color(0xFFD8F7E8) : const Color(0xFFFFE4F0),
            ),
          ),
        ),
      ),
    );
  }
}

class CreateOrderPage extends StatefulWidget {
  const CreateOrderPage({super.key, required this.user});

  final UserProfile user;

  @override
  State<CreateOrderPage> createState() => _CreateOrderPageState();
}

class _CreateOrderPageState extends State<CreateOrderPage> {
  final pickupCtrl = TextEditingController();
  final dropoffCtrl = TextEditingController();
  final itemCtrl = TextEditingController(text: 'Documents');
  final distanceCtrl = TextEditingController(text: '5');
  final cardCtrl = TextEditingController();
  String? payStatus;

  late PaymentProvider provider;

  List<PaymentProvider> get providers =>
      PlatformRegistry.of(widget.user.platform).paymentProviders(widget.user.country);

  double get fee => estimateFee(widget.user.country, double.tryParse(distanceCtrl.text) ?? 0);

  @override
  void initState() {
    super.initState();
    provider = providers.first;
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Create Delivery Order')),
      body: ListView(
        padding: const EdgeInsets.all(16),
        children: [
          const PinkHeader(
            title: '安全送货下单',
            subtitle: 'Soft UI · Clear steps · Safer delivery for women',
          ),
          const SizedBox(height: 14),
          TextField(controller: pickupCtrl, decoration: const InputDecoration(labelText: 'Pickup Address')),
          const SizedBox(height: 12),
          TextField(controller: dropoffCtrl, decoration: const InputDecoration(labelText: 'Dropoff Address')),
          const SizedBox(height: 12),
          TextField(controller: itemCtrl, decoration: const InputDecoration(labelText: 'Item Description')),
          const SizedBox(height: 12),
          TextField(controller: distanceCtrl, decoration: const InputDecoration(labelText: 'Distance KM')),
          const SizedBox(height: 12),
          DropdownButtonFormField<PaymentProvider>(
            value: provider,
            decoration: const InputDecoration(labelText: 'Payment Provider'),
            items: providers.map((p) => DropdownMenuItem(value: p, child: Text(p.label))).toList(),
            onChanged: (v) => setState(() => provider = v ?? providers.first),
          ),
          const SizedBox(height: 12),
          Text(
            'Estimated fee: \$${fee.toStringAsFixed(2)}',
            style: const TextStyle(fontWeight: FontWeight.w700),
          ),
          const SizedBox(height: 12),
          TextField(controller: cardCtrl, decoration: const InputDecoration(labelText: 'Card Last 4 Digits')),
          const SizedBox(height: 16),
          ElevatedButton.icon(
            onPressed: () async {
              try {
                final tx = await mockPay(provider, cardCtrl.text.trim());
                final order = DeliveryOrder(
                  pickup: pickupCtrl.text.trim(),
                  dropoff: dropoffCtrl.text.trim(),
                  item: itemCtrl.text.trim(),
                  distanceKm: double.tryParse(distanceCtrl.text) ?? 0,
                  fee: fee,
                  provider: provider,
                  paid: true,
                );
                if (!mounted) return;
                setState(() => payStatus = 'Paid: $tx');
                Navigator.of(context).pop(order);
              } catch (e) {
                setState(() => payStatus = e.toString());
              }
            },
            icon: const Icon(Icons.payments_outlined),
            label: const Text('Submit & Pay'),
          ),
          if (payStatus != null) ...[
            const SizedBox(height: 8),
            Text(payStatus!),
          ],
        ],
      ),
    );
  }
}
